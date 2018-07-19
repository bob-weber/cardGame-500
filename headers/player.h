#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "card.h"

class Player : public QObject
{
		Q_OBJECT
	public:
		explicit Player(QObject *parent = nullptr);
		~Player();

		Q_PROPERTY(uint m_playerId
		           READ GetPlayerId
		           WRITE SetPlayerId)
		uint GetPlayerId() const;
		void SetPlayerId(uint);


		Q_PROPERTY(uint m_teamId
		           READ GetTeamId
		           WRITE SetTeamId)
		uint GetTeamId() const;
		void SetTeamId(uint);

		Q_PROPERTY(QString m_playerName
		           READ GetPlayerName
		           WRITE SetPlayerName)
		QString GetPlayerName();
		void SetPlayerName(QString name);


		Q_PROPERTY(uint m_maxNumOfCards
		           READ GetMaxNumOfCards
		           WRITE SetMaxNumOfCards)
		uint GetMaxNumOfCards() const;
		void SetMaxNumOfCards(uint);

		Q_PROPERTY(uint m_currentNumOfCards
		           READ GetCurrentNumOfCards
		           WRITE SetCurrentNumOfCards)
		uint GetCurrentNumOfCards() const;
		void SetCurrentNumOfCards(uint);

		Q_PROPERTY(uint m_cardRotation
		           READ GetCardRotation
		           WRITE SetCardRotation)
		uint GetCardRotation() const;
		void SetCardRotation(uint);

		Q_PROPERTY(uint m_numOfSelectedCards
		           READ GetNumOfSelectedCards
		           WRITE SetNumOfSelectedCards)
		uint GetNumOfSelectedCards() const;
		void SetNumOfSelectedCards(uint);

		/******************************************************************************************************************
		 * Adds a card to this player's hand.
		 *
		 * It searches the hand to see if there's room. If there is, the pointer to this
		 * card is copied to this hand, and a signal is generated that adds this card to the UI.
		 *
		 * If the hand is full, a runtime exception is thrown.
		 *
		 * Inputs:
		 *	m_hand:	The array of card pointers that make up the player's hand.
		 *	m_numOfCardsInHand: Incremented if a card is added to this hand.
		 *
		 * Outputs:
		 *	Returns the index into the player's hand to which the card was added.
		 *	if no empty slot is found, returns m_MaxNumOfCardsInHand, which is an invalid index.
		 *
		 * Exceptions:
		 *	- Throws a logic error if m_numOfCardsInHand indicates there's an empty card slot, but we cannot find one in
		 *		the hand.
		 *	-	Throws a runtime error if we have no room in the hand for the new card.
		 * Notes:
		 ******************************************************************************************************************/
		uint AddCard(Card *card);

		/******************************************************************************************************************
		 * Clears all cards from the hand. This means we set all card pointers to null.
		 *
		 * Inputs:	None
		 *
		 * Outputs:
		 *	m_hand:	The array of card pointers that make up the player's hand are set to null.
		 *	m_numOfCardsInHand: Cleared to 0, since we've turned in all of the cards.
		 *
		 * Exceptions:
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void RemoveAllCards();

		/******************************************************************************************************************
		 * Sets the specified card's orientation.
		 * Emits a signal to update the GUI for this card.
		 *
		 * Inputs:
		 *	 cardId:			The card to modify.
		 *	 orientation:	The orientation to set the card to.
		 *
		 * Outputs:
		 *	m_hand:	The specified card in the hand has it's orientation field udpated.
		 ******************************************************************************************************************/
		void SetCardOrientation(uint cardId, Card::Orientation orientation);

		/******************************************************************************************************************
		 * Toggles the specified card. Updates the counter that keeps track of how many cards are selected in this hand.
		 * The GUI is updated by MainWindow. When a card is left-clicked, the GUI selects/deselects this card, and then
		 * emits a signal to the game logic. The game logic will call this function to update the card's selection, and
		 * update a count of the selected cards.
		 *
		 * Inputs:
		 *	 card:		The card we want to select or deselect.
		 *
		 * Outputs:
		 *	 card:		The card's selection field is toggled.
		 *	 m_numOfSelectedCards: Count of the number of selected cards in this hand.
		 ******************************************************************************************************************/
		void ToggleCardSelection(Card* card);

		/******************************************************************************************************************
		 * A convenience function that deslects all cards. and zeroes out the player's selected card counter.
		 * A signal is emitted to update the GUI for each card.
		 *
		 * This function was created so that signals to update the GUI for cards are generated by Player.
		 *
		 * Inputs:
		 *	 m_hand:	Cards in the player's hand are all deselected.
		 *
		 * Outputs:
		 *	 card:		The card's selection field is set false.
		 *	 m_numOfSelectedCards: Reset to 0.
		 ******************************************************************************************************************/
		void DeselectAllCards();

		/******************************************************************************************************************
		 * Swaps 2 cards between 2 player's hands, this player, and player2.
		 *
		 * Inputs:
		 *	 m_hand:				This player's hand
		 *	 cardId:				The card in the player's hand to swap.
		 *   player2:				The other player to swap with.
		 *   player2CardId:	The card in the 2nd player's hand to swap with.
		 *
		 * Outputs:
		 *	m_hand in each player's hand is updated.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void SwapCards(uint cardId, Player* player2, uint player2cardId);

		/******************************************************************************************************************
		 * Sorts the cards in a player's hand. It retrieves the "sort value" of each card, and swaps them so they are
		 * in increasing order. The sorting is done in place.
		 *
		 * Inputs:
		 *	 m_hand:	The player's hand of cards.
		 *
		 * Outputs:
		 *	m_hand is updated.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void SortHand();

		/******************************************************************************************************************
		 * Get/set a card in the player's hand.
		 *
		 * Inputs:
		 *	 cardIndex:	The card in the hand to set or get.
		 *	 card: When setting, the card to set.
		 *
		 * Outputs:
		 *	m_hand is updated.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		Card *GetCard(uint cardIndex);
		void SetCard(uint cardIndex, Card* card);

		/******************************************************************************************************************
		 * Updates the talbe GUI for the given hand. This is hand after you've manipulated the cards, say with sorting,
		 * and didn't update after each card change.
		 *
		 * The design approach is to always update the table through Player, since this class knows where each card is
		 * located.
		 *
		 * Inputs:
		 *	 m_hand:	A signal is emitted for each card in the player's hand.
		 *
		 * Outputs:
		 *	No variables. Only the GUI is refreshed.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void RefreshHand();

		/******************************************************************************************************************
		 * A debugging function to print a player's hand to the console.
		 *
		 * Inputs:
		 *	 m_hand:	Text is printed for each card in the player's hand.
		 *
		 * Outputs:
		 *	No variables. Only the GUI is refreshed.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void PrintHand();

	signals:
		/******************************************************************************************************************
		 * Signal emitted to update a player's card on the table GUI.
		 *
		 * Parameters:
		 *	 m_playerId:	The Id of this player. The GUI needs to know which player to update.
		 *	 cardIndex:		The index of the card to update. The GUI needs to know which card in the player's hand.
		 ******************************************************************************************************************/
		void CardChanged(uint m_playerId, uint cardIndex);

	public slots:

	private:

		uint m_playerId;				// Id of this player
		uint m_teamId;
		QString m_playerName;
		uint m_currentNumOfCards;
		uint m_maxNumOfCards;
		uint m_cardRotation;
		Card **m_hand;					// Array of card ptrs for the cards in the hand
		uint m_numOfSelectedCards;

		/******************************************************************************************************************
		 * Find an empty card slot in a player's hand.
		 *
		 * Inputs:
		 *	m_hand:	The array of card pointers that make up the player's hand.
		 *
		 * Outputs:
		 *	Returns the index into the array of cards for the hand.
		 *	if no empty slot is found, returns m_MaxNumOfCardsInHand, which is an invalid index.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		unsigned int FindEmptyHandSlot();

};

#endif // PLAYER_H
