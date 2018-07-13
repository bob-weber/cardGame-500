#ifndef BID_H
#define BID_H

#include <QObject>
#include <QString>

#include "game_settings.h"

class Bid : public QObject
{
		Q_OBJECT

	public:

		// Possible bids, suits and nellow
		enum bidSuitT { BID_SPADES, BID_CLUBS, BID_DIAMONDS, BID_HEARTS, BID_NO_TRUMP,
			              BID_NELLOW, BID_OPEN_NELLOW, BID_DOUBLE_NELLOW, BID_NUM_OF_SUITS };

		explicit Bid(uint playerId = NUM_OF_PLAYERS, uint numOfTricks = 0,
		             bidSuitT bid = BID_NUM_OF_SUITS, QObject *parent = nullptr);

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

		// Text for suits
		static const QString m_bidSuitText[BID_NUM_OF_SUITS];

};

#endif // BID_H
