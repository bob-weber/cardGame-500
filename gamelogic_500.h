#ifndef GAMELOGIC_500_H
#define GAMELOGIC_500_H

#include <QObject>
#include "player.h"
#include "deck.h"

class gameLogic_500 : public QObject
{
		Q_OBJECT

	public:
		explicit gameLogic_500(QObject *parent = nullptr);
		~gameLogic_500();

	signals:
		void finished();
		void PlayerNameChanged(uint player, QString name);
		void PlayerActionChanged(uint player, QString name);
		void PlayerCardChanged(uint player, uint card, QImage image);

	public slots:
		void PlayGame();
		void Deal();

	private:
		/******************************************************************************************************************
		 * Deal cards to each of the players and the kitty.
		 *
		 * Inputs:	None
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
		void AddCardToPlayer(Player *player);

		void ReturnAllCards();

		const uint m_numOfPlayers = 4;
		const uint m_numOfCardsPerPlayer = 10;
		const uint m_numOfCardsInKitty = 5;

		Deck *deck;					// The deck we're playing with
		Player **m_player;	// Array of players
		Player *m_kitty;		// Pointer to the kitty
};

#endif // GAMELOGIC_500_H