#include <QMessageBox>

#include "deck.h"
#include "player.h"
#include "game_500_settings.h"
#include "utilities.h"
#include "bidding.h"
#include "score.h"
#include "mergecards.h"
#include "mainwindow.h"

#include "logic.h"

using namespace std;


logic::logic(Player **players, Deck *deck, QObject *parent) : QObject(parent)
{
	m_players = players;
	m_deck = deck;
	Q_UNUSED(parent);
}

void logic::SetupTable()
{

	// Initialize Score
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

}


uint logic::GetDealer() const {
	return this->m_dealer;
}

void logic::SetDealer(uint dealer) {
	this->m_dealer = dealer;
}

void logic::NewGame()
{
	m_gameState = GAME_NEW_GAME;
	// The deal starts with player 0
	m_dealer = 0;
	m_gameScore->ClearTeamScores();
	emit TeamScoreChanged(0, m_gameScore->GetTeamScore(0));
	emit TeamScoreChanged(1, m_gameScore->GetTeamScore(1));

	NewHand();
}

void logic::NewHand()
{
	m_gameState = GAME_NEW_HAND;
	// Return all cards, shuffle the deck, and deal
	// All of these are non-blocking.
	// Return all cards from the players and the kitty
	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		m_players[playerIndex]->RemoveAllCards();
	}

	m_deck->Shuffle();
	DealCards();
	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		m_players[playerIndex]->SortHand();
		m_players[playerIndex]->RefreshHand();
	}
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
	bidding->GetAllBids(m_dealer, m_players);
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

	// Create the merge task, with the two players who's cards we'll merge.
	MergeCards *mergeCards = new MergeCards();

	// Pass the card selection siganl to mergeCards, so it knows to check how many cards are selected.
	connect(this, &logic::CardSelectionChanged, mergeCards, &MergeCards::UpdateCardSelection);

	connect(mergeCards, &MergeCards::MergingComplete, this, &logic::MergeComplete);

	// Start the merge
	mergeCards->StartMerge(m_players[m_currentBid->GetPlayerId()], m_players[KITTY_INDEX]);
}

void logic::MergeComplete()
{
	m_gameState = GAME_PLAY_HAND;

}

void logic::UpdateCardSelection(uint playerId, uint cardId)
{
	Q_UNUSED(playerId);
	Q_UNUSED(cardId);
	// Re-emit for subtasks
	emit CardSelectionChanged();
}

void logic::UpdateCardOrientation(uint playerId, uint cardId)
{
	Q_UNUSED(playerId);
	Q_UNUSED(cardId);
}


void logic::DealCards()
{
	// Deal all cards
	// 10 go to each player, and 5 to the kitty.
	uint playerIndex = m_dealer;
	bool dealToKittyThisPass = false;
	uint cardIndex = 0;
	while (cardIndex < m_deck->GetTotalCardCount())
	{
		m_players[playerIndex]->AddCard(m_deck->GetNextCard());
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

