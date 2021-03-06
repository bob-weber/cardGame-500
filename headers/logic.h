#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QString>

#include "player.h"
#include "deck.h"
#include "game_500_settings.h"
#include "score.h"

class logic : public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(uint m_dealer
		           READ GetDealer
		           WRITE SetDealer)
		uint GetDealer() const;
		void SetDealer(uint);
		QString *GetPlayerName(uint playerIndex);

		explicit logic(Player **players, Deck *deck, QObject *parent = nullptr);
		~logic();

		//void AdvanceGame();
		void SetupTable();

	signals:
		void finished();
		void PlayerNameChanged(uint player, QString name);
		void PlayerActionChanged(uint player, QString action);
		void TeamNameChanged(uint teamId, QString name);
		void TeamScoreChanged(uint teamId, int teamScore);
		void SetPlayerCard(uint playerId, uint cardIndex, Card* card, Player* player);
		void GetPlayerBids(uint dealer, Player **playersInfo);
		void CardSelectionChanged(uint playerId, uint cardId);

	public slots:
		void NewGame();
		void BiddingComplete(Bid *bid);
		void PlayHand();
		void UpdateCardSelection(uint playerId, uint CardId);
		void UpdateCardOrientation(uint playerId, uint CardId);
		//void UpdateCard_merge(uint playerId, uint CardId);

	protected:

	private:

		void NewHand();

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

		void GetBids();

		/******************************************************************************************************************
		 * For the player and car index specified, gets the next card off the deck, adds it to the player's hand, and
		 * updates the GUI.
		 *
		 * Inputs:
		 *	playerID:	the player to which we're adding the card
		 *  card:			the card to add
		 *
		 * Outputs:
		 *	m_player[x]->m_card:	Updated hands for each player
		 *	m_kitty->m_card:	Updated hand for the kitty
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void AddCardToPlayer(uint playerId, Card * card);

		/******************************************************************************************************************
		 * Merge the kitty with the hand of the specified player. The user selects the cards from the kitty that the
		 * player wants to take, and an equal number of cards from their hand that they want to trade. When ready, they
		 * select "Ok" on the pop-up window to exchange the cards. The kitty is then removed from the table top.
		 *
		 * Inputs:
		 *	m_currentBide:	Uses this class data to determine which player to merge the kitty with.
		 *
		 * Outputs:
		 *	Updated cards in the player's hand.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void MergeKittyWithHand();

		/******************************************************************************************************************
		 * Update the card image on the table. This doesn't implement any logic like flipping the card; it's just a common
		 * interface for updating the GUI.
		 *
		 * Inputs:
		 *	player:				GUI location: The player with the card.
		 *  card:					GUI location: card offset in the player's hand.
		 *  orientation:	Whether the card is face up or down.
		 *  rotation:			The degrees to rotate the card.
		 *  raised:				Raise or lower the card image. Used to show selection.
		 *
		 * Outputs:
		 *	Signal emitted to GUI to updat the card image.
		 *
		 * Notes:
		 ******************************************************************************************************************/

		void ScoreHand();

		void TurnPlayersCards(uint playerId, Card::Orientation orientation);

		// Keep track of what state we're in
		enum GameStateT { GAME_IDLE, GAME_NEW_GAME, GAME_NEW_HAND, GAME_BID, GAME_MERGE_KITTY, GAME_PLAY_HAND, GAME_SCORE };
		GameStateT m_gameState;
		//bool m_WaitingForStateComplete;

		Player **m_players;
		Deck* m_deck;

		// Keep track of which player is currently active (bidding, playing, etc.)
		//uint m_activePlayer;
		uint m_dealer;			// dealer for this round

		Bid *m_currentBid;
		Score *m_gameScore;
};

#endif // LOGIC_H
