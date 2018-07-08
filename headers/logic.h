#ifndef GAMELOGIC_500_H
#define GAMELOGIC_500_H

#include <QWidget>
#include "headers/player.h"
#include "headers/deck.h"

class gameLogic_500 : public QWidget
{
		Q_OBJECT

	public:
		explicit gameLogic_500(QWidget *parent = nullptr);
		~gameLogic_500();

		enum bid_suit { BID_SPADES, BID_CLUBS, BID_DIAMONDS, BID_HEARTS, BID_NO_TRUMP,
			              BID_NELLOW, BID_OPEN_NELLOW, BID_DOUBLE_NELLOW, BID_NUM_OF_SUITS };

		// This is the current bid. A valid bid replaces the existing bid, so we don't need to keep a record for each player.
		typedef struct {
			uint playerID;			// player with the current bid
			uint numOfTricks;		// # of tricks bid
			bid_suit suit;			// suit bid
		} bidT;

		void SetupTable();

	signals:
		void finished();
		void PlayerNameChanged(uint player, QString name);
		void PlayerActionChanged(uint player, QString name);
		void PlayerCardChanged(uint player, uint card, QImage image, uint rotation);

	public slots:
		void PlayGame();
		void Deal();
		void Bid();
		void CardClicked(uint player, uint card);
		void NewGame();

		void SetBid(gameLogic_500::bid_suit suit, uint numOfTricks);
		void SetBidPlayerID(uint ID);
		bidT *GetBid();

	private:
		/******************************************************************************************************************
		 * Deal cards to each of the players and the kitty.
		 *
		 * Inputs
		 *	None passed, but uses the private variable m_dealer to determine where to start the deal.
		 *
		 * Outputs:
		 *	None directly. Calls "DealCards" to update the class variables.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void DealCards();

		/******************************************************************************************************************
		 * For the player and car index specified, gets the next card off the deck, adds it to the player's hand, and
		 * updates the GUI.
		 *
		 * Inputs:
		 *	player:	the player to which we're adding the card
		 *
		 * Outputs:
		 *	m_player[x]->m_card:	Updated hands for each player
		 *	m_kitty->m_card:	Updated hand for the kitty
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void AddCardToPlayer(Player *, Card *);
		void ReturnAllCards();

		uint advanceIndex(uint index, const uint max);

		Deck *deck;					// The deck we're playing with
		Player **m_player;	// Array of players

		// Keep track of which player is currently active (bidding, playing, etc.)
		uint m_activePlayer;
		uint m_dealer;			// dealer for this round

		bidT m_bidStatus;
};

#endif // GAMELOGIC_500_H
