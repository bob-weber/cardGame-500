#ifndef LOGIC_H
#define LOGIC_H

#include <QWidget>
#include <QString>

#include "player.h"
#include "deck.h"
#include "game_settings.h"
#include "bid.h"

class logic : public QWidget
{
		Q_OBJECT

	public:
		explicit logic(QWidget *parent = nullptr);
		~logic();

		void SetupTable();

		Q_PROPERTY(uint m_dealer
		           READ GetDealer
		           WRITE SetDealer)
		uint GetDealer() const;
		void SetDealer(uint);
		QString *GetPlayerName(uint playerIndex);

	signals:
		void finished();
		void PlayerNameChanged(uint player, QString name);
		void PlayerActionChanged(uint player, QString name);
		void PlayerCardChanged(uint player, uint card, QImage image, uint rotation);

	public slots:
		void PlayGame();
		void Deal();
		void CardClicked(uint player, uint card);
		void NewGame();
		bool GetBids();

	protected:
		typedef struct {
			QString name;
			uint GUI_ID;
			uint maxNumOfCards;
			uint currentNumOfCards;
			uint cardRotation;
			uint teamID;	// 0=no team. >0 with the same id groups players on a team.
		} playerT;
		playerT m_PlayerInfo[NUM_OF_HANDS] =
		{
		  // ID 0-3 are the regular players
		  // ID 4 is the kitty
		  // ID         GUI ID  Max # Cards               Current # Cards  Card Rotation  Team ID
		  // ---------  ------  ------------------------  ---------------  -------------  -------
		  { "Kathy",        0,  NUM_OF_CARDS_PER_PLAYER,               0,             0,       1 },
		  { "Theodore",     1,  NUM_OF_CARDS_PER_PLAYER,               0,            90,       2 },
		  { "Priya",        2,  NUM_OF_CARDS_PER_PLAYER,               0,           180,       1 },
		  { "Edward",       3,  NUM_OF_CARDS_PER_PLAYER,               0,           270,       2 },
		  { "",             4,    NUM_OF_CARDS_IN_KITTY,               0,             0,       0 }
		};

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

		Deck *deck;					// The deck we're playing with
		Player **m_player;	// Array of players

		// Keep track of which player is currently active (bidding, playing, etc.)
		//uint m_activePlayer;
		uint m_dealer;			// dealer for this round

		Bid *m_currentBid;

		uint m_nellowTeamId;	// Id of team that bids nellow

};

#endif // LOGIC_H
