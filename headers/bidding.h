#ifndef BIDDING_H
#define BIDDING_H

#include <QObject>
#include <QWidget>
#include <QString>
#include "bid.h"
#include "player.h"
#include "game_settings.h"

/**********************************************************************************************************************
 * This class encapsulates the bidding actions.
 **********************************************************************************************************************/

class Bidding : public QObject
{
		Q_OBJECT

	public:

		/******************************************************************************************************************
		 * Constructor. Creates a bid object, where we'll save the highest bid, as we get bids from players.
		 * We allocate this memory in the constructor and delete it in the destructor.
		 *
		 * Inputs: None
		 *
		 * Outputs:
		 *   m_highestBid:	Set to a new bid object to be updated as we get bids.
		 *
		 * Notes:	None
		 ******************************************************************************************************************/
		explicit Bidding(QObject *parent = nullptr);
		~Bidding();

		/******************************************************************************************************************
		 * Launches the dialog box for the specified player, to get their bid.
		 * The dialog is non-modal, so the user can interact with the table, flip cards, etc.
		 *
		 * Inputs
		 *	 m_bidder:		The Id of the player for which we'll get the bid.
		 *	 m_players:		Player info array. Needed to get the name of the player we'll display in the dialog.
		 *
		 * Outputs:	None
		 *
		 * Notes:	None
		 ******************************************************************************************************************/
		void GetAllBids(uint dealer, Player** players);

	signals:
		/******************************************************************************************************************
		 * A signal to update the player's action/status message on the table.
		 *
		 * Inputs:	None
		 *
		 * Outputs:
		 *   playerId:	The player Id to update
		 *	 message:		The action/status message to display
		 ******************************************************************************************************************/
		void PlayerActionChanged(uint playerId, QString message);

		/******************************************************************************************************************
		 * A signal indicating the winning bid to the game logic object.
		 *
		 * Inputs:	None
		 *
		 * Outputs:
		 *   bid:		The winning bid
		 ******************************************************************************************************************/
		void BiddingIsComplete(Bid *bid);

	public slots:
		/******************************************************************************************************************
		 * This is a slot received from the bidding dialog box, which gets each player's bid.
		 * It verifies the bid is a valid bid, or a pass.
		 * 1. The player's bid score > the current bid score.
		 * 2. If the bid is double nellow, the player's partner has already bid nellow.
		 *
		 * This function also updates the action/status messages on the table, indicating who has bid, who is bidding,
		 * who is waiting, and who has been outbid.
		 *
		 * If the player has a valid bid or has passed, the function updates the current bid and starts the bidding for
		 * the next player. When all players have bid, it notifies the caller with the complete bid, and exits.
		 *
		 * Inputs
		 *	 playerBid:			The bid for this player.
		 * 	 m_currentBid:	The current bid. This may be a previous player's bid, or it may be invalid, if no one has bid.
		 *
		 * Outputs:
		 *   m_currentBid:	Updates the current bid if this is valid.
		 *	 m_completedBidCount:	Keeps track of how many players have bid, so we know when all players have bid.
		 *	 m_bidder:			Advances to the next bidder, if this bid is valid or pass.
		 * Notes:	None
		 ******************************************************************************************************************/
		void VerifyPlayerBid(Bid* playerBid);


	private:
		/******************************************************************************************************************
		 * Initiates getting bids from each player.
		 * Bidding starts with the player to the left of the dealer.
		 * It also sets all of the player's action/status to "Waiting", and indicates the dealer, on the table.
		 *
		 * Inputs
		 *	 dealer:		The Id of the dealer for this hand
		 *	 players:	Player info array
		 *
		 * Outputs:
		 *	 m_bidder:	Bidder Id
		 *   m_players:	Saved pointer to the player information
		 *
		 * Notes:	None
		 ******************************************************************************************************************/
		void GetOneBid();

		Bid *m_highestBid;				// highest bid in this round of bidding
		uint m_bidder;						// Current bidder
		Player** m_players;				// Player information
		uint m_nellowTeamId;			// Id of team that bid nellow
		uint m_completedBidCount;	// How many players have completed bidding
};

#endif // BIDDING_H
