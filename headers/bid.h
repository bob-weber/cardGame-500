#ifndef BID_H
#define BID_H

#include <QObject>
#include <QWidget>
#include <QString>

#include "game_settings.h"

class Bid : public QWidget
{
		Q_OBJECT

	public:

		// Possible bids, suits and nellow
		enum bidSuitT { BID_SPADES, BID_CLUBS, BID_DIAMONDS, BID_HEARTS, BID_NO_TRUMP,
			              BID_NELLOW, BID_OPEN_NELLOW, BID_DOUBLE_NELLOW, BID_NUM_OF_SUITS };

		explicit Bid(uint playerID = NUM_OF_PLAYERS, uint numOfTricks = 0, bidSuitT suit = BID_NUM_OF_SUITS, QWidget *parent = nullptr);

		Q_PROPERTY(uint m_playerId
		           READ GetPlayerId
		           WRITE SetPlayerId)
		uint GetPlayerId() const;
		void SetPlayerId(uint);

		Q_PROPERTY(uint m_numOfTricks
		           READ GetNumOfTricks
		           WRITE SetNumOfTricks)
		uint GetNumOfTricks() const;
		void SetNumOfTricks(uint);

		Q_PROPERTY(bidSuitT m_bidSuit
		           READ GetBidSuit
		           WRITE SetBidSuit)
		bidSuitT GetBidSuit() const;
		void SetBidSuit(bidSuitT);

		// Convencience operators
		bool operator==(Bid &bid) {
			return ((this->m_playerId    == bid.m_playerId) &&
			        (this->m_numOfTricks == bid.m_numOfTricks) &&
			        (this->m_bidSuit     == bid.m_bidSuit))
			       ? true : false;
		}

		Bid& operator=(Bid& bid) {
			this->m_playerId    = bid.m_playerId;
			this->m_numOfTricks = bid.m_numOfTricks;
			this->m_bidSuit     = bid.m_bidSuit;
			return *this;
		}

		/******************************************************************************************************************
		 * Get the bid for the specified player. This function will:
		 * 1. Open up a dialog to get the player's bid.
		 * 2. Verify the bid is valid. That is, has a non-zero value.
		 * 3. When closing the window, pop-up a confirmation window.
		 * 4. If confirmed, return. If not, allow user to change the bid.
		 *
		 * Inputs:
		 *	name:	The name of the player for which to get the bid
		 *	Id:		The player's ID, saved if the player makes a valid bid.
		 *
		 * Outputs:
		 *  Returns true if the player made a valid bid, false if not.
		 *	m_playerId:			Updated with the passed in player's ID.
		 *	m_numOfTricks:	The bid number of tricks.
		 *	m_bidSuit:			Updated with the player's bidding suit or a type of nellow.
		 *
		 * Notes:
		 *	If no player bids, it's up to the calling function take the appropriate action.
		 ******************************************************************************************************************/
		bool GetPlayerBid(QString name, uint Id);

		/******************************************************************************************************************
		 * Get a QString that has the spelled out bidding suit, such as "Clubs" or "Nellow".
		 *
		 * Inputs:
		 *	m_bidSuit: This class' current bid suit.
		 *
		 * Outputs:
		 *  Returns a QString with the text of the bid suit.
		 *
		 * Notes:
		 *	None
		 ******************************************************************************************************************/
		QString GetSuitText();

		/******************************************************************************************************************
		 * Get a QString that indicates the bid, such as "6 Clubs" or "Nellow".
		 *
		 * Inputs:
		 *	m_numOfTricks:	The current number of tricks bid.
		 *	m_bidSuit:			The current bid suit.
		 *
		 * Outputs:
		 *  Returns a QString with the text of the bid.
		 *
		 * Notes:
		 *	None
		 ******************************************************************************************************************/
		QString GetBidText();

		/******************************************************************************************************************
		 * Checks if this bid is valid (has a score > 0).
		 *
		 * Inputs
		 *	m_numOfTricks:	this bid's number of tricks
		 *	m_bidSuit: this bid's bidding suit
		 *
		 * Outputs:
		 *	Returns true if valid
		 *
		 * Notes:
		 ******************************************************************************************************************/
		bool IsValid();

		/******************************************************************************************************************
		 * Get the scoring value of the current bid.
		 *
		 * Inputs
		 *	numOfTricks: The number of tricks for the bid.
		 *  suit:		The bid suit, or nellow.
		 *
		 * Outputs:
		 *	Returns the scoring value of the bid.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		uint GetScore();

		/******************************************************************************************************************
		 * Clear the bid. This is done' to clear the slate for a new round of bidding.
		 *
		 * Inputs
		 *	None
		 *
		 * Outputs:
		 *	None
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void Clear();

	signals:

	public slots:

	private:
		// Current bid. This is the currently winning bid for a hand.
		uint  m_playerId;			// player with the current bid
		uint  m_numOfTricks;	// # of tricks bid
		bidSuitT m_bidSuit;		// suit bid

		// Scoring for current bids
		const uint Score[Bid::BID_NUM_OF_SUITS][NUM_OF_CARDS_PER_PLAYER] =
		{	//   1    2    3    4    5    6    7    8    9    10
		  // ----  ---  ---  ---  ---  ---  ---  ---  ---  ---
		  {     0,   0,   0,   0,   0,  40, 140, 240, 340, 440 },	// Spades bid
		  {     0,   0,   0,   0,   0,  60, 160, 260, 360, 460 },	// Clubs bid
		  {     0,   0,   0,   0,   0,  80, 180, 280, 380, 480 },	// Diamonds bid
		  {     0,   0,   0,   0,   0, 100, 200, 300, 400, 500 },	// Hearts bid
		  {     0,   0,   0,   0,   0, 120, 220, 320, 420, 520 },	// No Trump bid
		  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 250 },	// Nellow bid
		  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 500 },	// Open nellow bid
		  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 500 },	// Double nellow bid
		};

		QString m_bidSuitText[BID_NUM_OF_SUITS] = {
		  "Spades", "Clubs", "Diamonds", "Hearts", "No Trump", "Nellow", "Open Nellow", "Double Nellow"
		};

};

#endif // BID_H
