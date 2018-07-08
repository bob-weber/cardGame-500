#include "user_bid_dialog.h"
#include "game_settings.h"
#include "utilities.h"

#include "logic.h"

void logic::SetBid(bid_suit suit, uint numOfTricks)
{
	this->m_bidStatus.suit = suit;
	this->m_bidStatus.numOfTricks = numOfTricks;
}

void logic::SetBidPlayerID(uint ID)
{
	this->m_bidStatus.playerID = ID;
}

logic::bidT *logic::GetBid()
{
	return &(this->m_bidStatus);
}

/******************************************************************************************************************
 * Starting with the player to the left of the dealer, get bids.
 * Verify each successive bid is > than the current bid. When the dealer has bid, bidding is complete.
 * Return to the calling function.
 *
 *
 * Inputs:
 *	startingPlayer:	The index of the player who'll start the bidding.
 *
 * Outputs:
 *	m_bidStatus: Keeps track of the current and winning bid.
 *
 * Notes:
 *	If no player bids, it's up to the claling function to check for this, and reshuffle the cards.
 ******************************************************************************************************************/
void logic::GetPlayerBids(uint startingPlayer)
{
	// We set the current bid to 1 spade. This isn't a valid bid, and the value is 0.
	m_currentBid.numOfTricks = 1;
	m_currentBid.suit = BID_SPADES;

	// Get the bid for each player, starting to the left of the dealer
	uint activePlayer = advanceIndex(startingPlayer, NUM_OF_PLAYERS);
	for (uint i=0; i < (NUM_OF_HANDS-1); i++)
	{
		QString name = GetPlayerName(activePlayer);
		UserBidDialog dialog(&name, BidValue[m_currentBid.suit][m_currentBid.numOfTricks]);
		//userBidForm.setWindowModality(Qt::Modaless);
		// bidUI.setModal(true);	// Block until the user enters a bid

		/* Connect signals/slots
		 * I had trouble getting the connection to work from within the dialog.
		 * It works making the connection here. Do this by default.
		 *
		 * old format: connect(&dialog, SIGNAL(BidComplete(logic::bid_suit,uint)), this, SLOT(SetBid(logic::bid_suit,uint)));
		 */
		connect(&dialog, &UserBidDialog::BidComplete, this, &logic::SetBid);

		auto test = dialog.exec();
		if (test == QDialog::Accepted)
		{
			activePlayer = advanceIndex(activePlayer, NUM_OF_PLAYERS);
		}
		else
		{	/* The user aborted the bid box
			 * What does that mean, they want to abort the game?
			 * Let's assume that's true. Otherwise, if they did want to, we'd be stuck in the bidding modal dialog,
			 * and they couldn't get to the main window to close it.
			 */
			exit(EXIT_SUCCESS);
		}
	}

}
