#include <QMessageBox>

#include "deck.h"
#include "player.h"
#include "game_settings.h"
#include "utilities.h"
#include "bidding.h"
#include "score.h"
#include "mergecards.h"

#include "logic.h"

using namespace std;


logic::logic(QObject *parent) : QObject(parent)
{
	/* Allocate player instances in the constructor
	 * Since we delete them in the destructor, it's more logical to allocate them here, rather than rely on
	 * another function being called after the constructor.
	 */
	m_player = new Player *[NUM_OF_HANDS];
	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		m_player[playerIndex] = new Player(playerIndex);
		connect(m_player[playerIndex], &Player::SetPlayerCard, this, &logic::SetPlayerCard);
	}

	/* Do not do other initialization here that relies on signals and slots.
	 * The parent sets up these connections. We'll do this in SetupTable(), which the parent will call.
	 */
}

void logic::SetupTable()
{
	/********************************************************************************************************************
	 * Setup the deck, players, etc.
	 ********************************************************************************************************************/
	// Create a deck
	deck = new Deck(Deck::DECK_4S_AND_UP, 1, 1);
	//deck->Print();

	// Initialize the players
	for (uint playerIndex = 0; playerIndex < NUM_OF_PLAYERS; playerIndex++)
	{
		// Set each player's ID
		Player *player = m_player[playerIndex];
		player->SetPlayerName(m_PlayerInfo[playerIndex].name);
		player->SetTeamId(m_PlayerInfo[playerIndex].teamID);

		// All players start of with no cards
		player->SetCurrentNumOfCards(0);
		player->SetMaxNumOfCards(NUM_OF_CARDS_PER_PLAYER);
		// Set the card's rotation on the GUI
		player->SetCardRotation(m_PlayerInfo[playerIndex].cardRotation);

		emit PlayerNameChanged(playerIndex, player->GetPlayerName());
		emit PlayerActionChanged(playerIndex, "");
	}	// for each player

	// Initialize the kitty
	Player *kitty = m_player[KITTY_INDEX];
	kitty->SetPlayerName(m_PlayerInfo[KITTY_INDEX].name);
	kitty->SetCurrentNumOfCards(0);
	kitty->SetMaxNumOfCards(NUM_OF_CARDS_IN_KITTY);
	kitty->SetCardRotation(m_PlayerInfo[KITTY_INDEX].cardRotation);

	// Initialize Score
	QString teamName = QString("%1/%2").arg(m_player[0]->GetPlayerName()).arg(m_player[2]->GetPlayerName());
	emit TeamNameChanged(0, teamName);
	teamName = QString("%1/%2").arg(m_player[1]->GetPlayerName()).arg(m_player[3]->GetPlayerName());
	emit TeamNameChanged(1, teamName);

	m_gameScore = new Score();
	m_gameScore->ClearTeamScores();
	emit TeamScoreChanged(0, m_gameScore->GetTeamScore(0));
	emit TeamScoreChanged(1, m_gameScore->GetTeamScore(1));

	// Deal cards so we replace the label text with the card images.
	m_dealer = 0;
	DealCards();

	// Game is idle until the player takes some action
	m_gameState = GAME_IDLE;
	//m_WaitingForStateComplete = false;

}


logic::~logic()
{
	// Delete players
	for (uint i = 0; i < NUM_OF_HANDS; i++)
	{
		delete m_player[i];
	}
	delete[] m_player;
}


uint logic::GetDealer() const {
	return this->m_dealer;
}

void logic::SetDealer(uint dealer) {
	this->m_dealer = dealer;
}

QString *logic::GetPlayerName(uint playerIndex) {
	return &m_PlayerInfo[playerIndex].name;
}

void logic::NewGame()
{
	m_gameState = GAME_NEW_GAME;
	// The deal starts with player 0
	m_dealer = 0;
	m_gameScore->ClearTeamScores();
	NewHand();
}

void logic::NewHand()
{
	m_gameState = GAME_NEW_HAND;
	// Return all cards, shuffle the deck, and deal
	// All of these are non-blocking.
	ReturnAllCards();
	deck->Shuffle();
	DealCards();
	GetBids();
}

void logic::GetBids()
{
	m_gameState = GAME_BID;
	/* Create a bidding object, passing a reference to player info.
	 */
	Bidding *bidding = new Bidding();
	connect(bidding, &Bidding::PlayerActionChanged, this, &logic::PlayerActionChanged);
	connect(bidding, &Bidding::BiddingIsComplete, this, &logic::BiddingComplete);
	bidding->GetAllBids(m_dealer, m_player);
	// When done, "bidding" will emit BiddingComplete().
}

void logic::BiddingComplete(Bid *bid)
{
	if (bid->IsValid())
	{	// We have a valid bid for this hand
		m_currentBid = bid;
		MergeKittyWithHand();
	}
	else
	{	// No one bid
		QMessageBox msgBox;
		msgBox.setText("No one bid. We'll redeal and try again.");
		msgBox.setInformativeText("No valid bid");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.exec();
		NewHand();
	}
}

void logic::MergeKittyWithHand()
{
	m_gameState = GAME_MERGE_KITTY;
	/* We're going to allow the user to select cards from the winning bidder and the kitty.
	 * A pop-up dialog will explain how to perform the merge, and to click the "Ok" button when finished.
	 * This pop-up needs to be non-modal, so a player can see the cards on the GUI. We'll accomplish this
	 * by running the merge cards task and dialog in a separate thread.
	 *
	 * When the user clicks Ok, and valid cards have been selected, the merge task will exchange the cards
	 * and exit, returning control to this function.
	 */

	// Turn all the cards in the player's hand, and the kitty, face-up
//	TurnPlayersCards(m_currentBid->GetPlayerId(), Card::FACE_UP);
//	TurnPlayersCards(KITTY_INDEX, Card::FACE_UP);

	// Create the merge task, with the two players who's cards we'll merge.
	MergeCards *mergeCards = new MergeCards();
//	mergeCards->MergeHandsd(m_player[m_currentBid->GetPlayerId()], m_player[KITTY_INDEX]);
//	connect(this, &logic::CardSelected, mergeCards, &MergeCards::CardSelectionChanged);
//	connect(mergeCards, &MergeCards::CardChanged, this, &logic::UpdateCardOnTable);

//	        UpdateCardOnTable(uint player, uint card, Card::Orientation orientation, uint rotation, bool isSelected);

}

void logic::MergingCardsComplete()
{
	// Todo: Play hand
}


void logic::ReturnAllCards()
{
	// Return all cards from the players and the kitty
	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		m_player[playerIndex]->RemoveAllCardsFromHand();
	}
}

void logic::DealCards()
{
	// Deal all cards
	// 10 go to each player, and 5 to the kitty.
	uint playerIndex = m_dealer;
	bool dealToKittyThisPass = false;
	uint cardIndex = 0;
	while (cardIndex < deck->GetTotalCardCount())
	{
		m_player[playerIndex]->AddCardToHand(deck->GetNextCard());
		++cardIndex;

		// Advance to the next player
		// We include the kitty in this sequence, but if it's not time to deal to the kitty, we'll skip it.
		playerIndex = advanceIndex(playerIndex, NUM_OF_HANDS);
		if (playerIndex == KITTY_INDEX)
		{	// Next index is to deal to the kitty
			if (dealToKittyThisPass)
			{	// Do nothing with the index. We're going to do that on the next pass.
				// Clear the flag for the next pass.
				dealToKittyThisPass = false;
			}
			else
			{	// We're not going to deal to the kitty
				// Advance the pointer again, past the kitty
				playerIndex = advanceIndex(playerIndex, NUM_OF_HANDS);
				// Set the flag for the next pass.
				dealToKittyThisPass = true;
			}
		}
		// else, not the kitty
		// Nothing special to do
	}	// while
}

