#include <QMessageBox>

#include "deck.h"
#include "player.h"
#include "game_settings.h"
#include "utilities.h"
#include "bid.h"
#include "user_bid_dialog.h"


#include "logic.h"

using namespace std;


logic::logic(QWidget *parent) : QWidget(parent)
{
	/* Allocate player instances in the constructor
	 * Since we delete them in the destructor, it's more logical to allocate them here, rather than rely on
	 * another function being called after the constructor.
	 */
	m_player = new Player *[NUM_OF_HANDS];
	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		m_player[playerIndex] = new Player();

	}

	/* Do not do other initialization here that relies on signals and slots.
	 * The parent sets up these connections. We;ll do this in SetupTable(), which the parent will call.
	 */
}

void logic::SetupTable()
{
	/********************************************************************************************************************
	 * Setup the deck, players, etc.
	 ********************************************************************************************************************/
	// Create a deck
	deck = new Deck(Deck::DECK_4S_AND_UP, 1, 1);
	deck->Print();

	// Initialize the playersDealCards
	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		// Set each player's ID
		m_player[playerIndex]->SetID(m_PlayerInfo[playerIndex].GUI_ID);

		// All players start of with no cards
		m_player[playerIndex]->SetCurrentNumOfCards(0);

		// Max # of cards depends on whether this is a normal player or the kitty
		m_player[playerIndex]->SetMaxNumOfCards(m_PlayerInfo[playerIndex].maxNumOfCards);

		if (playerIndex < KITTY_INDEX)
		{	// Not the kitty
			// Update the player's GUI name
			emit PlayerNameChanged(m_PlayerInfo[playerIndex].GUI_ID, m_PlayerInfo[playerIndex].name);
			emit PlayerActionChanged(m_PlayerInfo[playerIndex].GUI_ID, "");
		}

		// Set the card's rotation on the GUI
		m_player[playerIndex]->SetCardRotation(m_PlayerInfo[playerIndex].cardRotation);
	}

	/* Create the currently valid bid
	 * We use this throughout the game.
	 * The player ID is set to NUM_OF_PLAYERS, which isn't a valid ID.
	 */
	m_currentBid = new Bid();

	// Start dealing with player 0
	m_dealer = 0;
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


uint logic::GetDealer() const
{
	return this->m_dealer;
}

void logic::SetDealer(uint dealer)
{
	this->m_dealer = dealer;
}

QString *logic::GetPlayerName(uint playerIndex)
{
	return &m_PlayerInfo[playerIndex].name;
}


void logic::PlayGame()
{
	/********************************************************************************************************************
	 * Start a new game
	 * This returns when the game is complete.
	 ********************************************************************************************************************/
	Deal();
	//NewGame();

	// TODO: pop-up to display winner
}

void logic::NewGame()
{
	// The deal starts with player 0
	m_dealer = m_PlayerInfo[0].GUI_ID;

	// Get bids from each player
	m_currentBid->Clear();
	bool successfulBid = false;
	while (!successfulBid)
	{
		Deal();

		successfulBid = GetBids();
		if (!successfulBid)
		{
			QMessageBox msgBox;
			msgBox.setText("No one bid. We'll redeal and try again.");
			msgBox.setInformativeText("No valid bid");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();
		}
	}	// while

	//PlayHand();
	//Score();
}

bool logic::GetBids()
{
	// Bidding starts left of the dealer. Set to dealer. We'll advance it below.
	uint bidder = m_dealer;

	// Set all player actions to waiting to bid
	QString bidMsg = QString("Waiting");
	for (uint i=0; i < NUM_OF_PLAYERS; i++)
	{
		emit PlayerActionChanged(m_PlayerInfo[i].GUI_ID, bidMsg);
	}

	// Get a bid for each player
	bool someoneBid = false;
	m_nellowTeamId = NUM_OF_PLAYERS;
	for (uint i=0; i < NUM_OF_PLAYERS; i++)
	{
		// start bidding to the left of the dealer
		bidder = advanceIndex(bidder, NUM_OF_PLAYERS);
		emit PlayerActionChanged(bidder, "Bidding");
		uint bidScore;

		bool validBidOrPass = false;
		while (!validBidOrPass)
		{
			// This is the start of a player's bidding, so zero out the player's bid
			Bid *playerBid = new Bid(bidder, 0, Bid::BID_NUM_OF_SUITS);
			UserBidDialog dialog(GetPlayerName(bidder), playerBid);
			auto test = dialog.exec();
			if (test == QDialog::Accepted)
			{	// The player completed their bid or passed
				bidScore = playerBid->GetScore();
				if (bidScore > 0)
				{	// The player bid something
					if (bidScore > m_currentBid->GetScore())
					{	// This bid is > than our current bid
						if (playerBid->GetBidSuit() == Bid::BID_NELLOW)
						{	// Save nellow bid info in case someone later bids double nellow
							/* We don't need to verify nellow hasn't already been bid in this round
							 * because if it had, bidScore wouldn't be > the current score.
							 */
							validBidOrPass = true;
							m_nellowTeamId = m_PlayerInfo[bidder].teamID;
						}
						else if (playerBid->GetBidSuit() == Bid::BID_DOUBLE_NELLOW)
						{
							// Double nellow is only valid if partner bid nellow
							if (m_PlayerInfo[bidder].teamID == m_nellowTeamId)
							{	// This is a valid double nellow bid
								validBidOrPass = true;
							}
							// else, invalid double nellow bid
						}
						else
						{	// Valid suit/# of tricks bid
							validBidOrPass = true;
						}
					}
					else
					{	// Bid doesn't exceed current bid
					}
				}
				else
				{	// No bid
					validBidOrPass = true;
				}

				if (validBidOrPass)
				{	// Bid is valid
					if (bidScore > 0)
					{	// This is an actual bid
						someoneBid = true;

						// See if current bid is a valid player's bid. If it is, we're replacing an existing bid.
						if (m_currentBid->GetPlayerId() < NUM_OF_PLAYERS)
						{	// This bid has been superseded
							// Set this player's action to "Outbid"
							emit PlayerActionChanged(m_currentBid->GetPlayerId(), "Bid: Outbid");
						}

						// Update the current bid
						m_currentBid = playerBid;

						// Set this player's action to their bid
						QString bidMsg = QString("Bid: %1").arg(m_currentBid->GetBidText());
						emit PlayerActionChanged(m_currentBid->GetPlayerId(), bidMsg);
					}
					else
					{	// This player passed
						emit PlayerActionChanged(bidder, "Bid: Passed");
					}
				}
				else
				{	/* Not a valid bid
					 * This is because one of the following are true:
					 * 1. The bid amount score is < the current bid, or
					 * 2. The bid is double nellow, but their partner hasn't bid nellow
					 */
					if (playerBid->GetBidSuit() == Bid::BID_DOUBLE_NELLOW)
					{	// Invalid double nellow bid
						QMessageBox msgBox;
						QString msg = QString("%1, your bid of %2 is invalid.")
						    .arg(*GetPlayerName(bidder)).arg(playerBid->GetBidText());
						QString informativeMsg = QString("%1 requires your parter bid Nellow.\n\rSelect Ok to re-bid.")
						    .arg(playerBid->GetBidText()).arg(m_currentBid->GetScore()).arg(playerBid->GetScore());
						msgBox.setText(msg);
						msgBox.setInformativeText(informativeMsg);
						msgBox.setStandardButtons(QMessageBox::Ok);
						msgBox.setDefaultButton(QMessageBox::Ok);
						msgBox.exec();
						// validBidOrPass == false will result in user rebidding
					}
					else
					{	// Bid score is too low
						QMessageBox msgBox;
						QString msg = QString("%1, your bid of %2 is invalid.")
						    .arg(*GetPlayerName(bidder)).arg(playerBid->GetBidText());
						QString informativeMsg = QString("The current game bid is %1, and has a score of %2.\nThe score of your bid is %3.\n\rSelect Ok to Pass on bidding, or select Cancel to re-bid.")
						    .arg(m_currentBid->GetBidText()).arg(m_currentBid->GetScore()).arg(playerBid->GetScore());
						msgBox.setText(msg);
						msgBox.setInformativeText(informativeMsg);
						msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
						msgBox.setDefaultButton(QMessageBox::Ok);
						int ret = msgBox.exec();
						if (ret == QMessageBox::Ok)
						{	// The user has accepted a "Pass"
							// Don't update current bid.
							// We're done
							validBidOrPass = true;
							emit PlayerActionChanged(bidder, "Bid: Passed");
						}
						else
						{	// User has cancelled, meaning they want to rebid
							// Leave validBidOrPass false.
							// The while loop will redo the bidding dialog
						}
					}
				}
			}
			else
			{	/* The user aborted the bid box
				 * What does that mean, they want to abort the game?
				 * Let's assume that's true. Otherwise, if they did want to, we'd be stuck in the bidding modal dialog,
				 * and they couldn't get to the main window to close it.
				 */
				exit(EXIT_SUCCESS);
			}
		}	// while

	}	// for

	return someoneBid;
}

void logic::ReturnAllCards()
{
	// Return all cards from the players and the kitty
	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		m_player[playerIndex]->RemoveAllCardsFromHand();
	}
}

void logic::Deal()
{
	ReturnAllCards();
	deck->Shuffle();
	DealCards();
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
		AddCardToPlayer(m_player[playerIndex], deck->GetNextCard());
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



void logic::CardClicked(uint player, uint card)
{
	Card *playerCard = nullptr;
	uint cardRotation = 0;
	// Find the player that matches our player index
	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		if (m_player[playerIndex]->GetID() == player)
		{	// This is the player who's card was clicked
			playerCard = m_player[playerIndex]->GetCard(card);
			cardRotation = m_player[playerIndex]->GetCardRotation();
			break;
		}
		// else, not the correct player
	}	// for

	if (playerCard != nullptr)
	{	// We have a valid card
		Card::Orientation orientation = playerCard->FlipOrientation();
		if (orientation == Card::FACE_DOWN) {
			emit PlayerCardChanged(player, card, playerCard->GetBackImage(), cardRotation);
		}
		else {
			emit PlayerCardChanged(player, card, playerCard->GetFaceImage(), cardRotation);
		}
	}
	// else, this card hasn't been dealt yet or we didn't find it
}

void logic::AddCardToPlayer(Player *player, Card *card)
{
	//cout << "player=" << playerIndex << ", card=" << cardIndex << endl;

	// Get the next card in the deck and add it to this player's hand.
	uint handIndex = player->AddCardToHand(card);

	if (handIndex < player->GetMaxNumOfCards())
	{	// We successfully added the card to this player's hand
		QImage image;
		if (card->GetOrientation() == Card::FACE_DOWN) {
			image = card->GetBackImage();
		}
		else {
			image = card->GetFaceImage();
		}

		// Update the GUI with this card.
		uint cardRotation = player->GetCardRotation();
		emit PlayerCardChanged(player->GetID(), handIndex, image, cardRotation);
	}
	else
	{
		throw out_of_range("logic::AddCardToPlayer: Couldn't add card to player.");
	}
}
