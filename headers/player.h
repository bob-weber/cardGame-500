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

		Q_PROPERTY(uint m_ID
		           READ GetID
		           WRITE SetID)
		uint GetID() const;
		void SetID(uint);

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
		uint AddCardToHand(Card *card);

		/******************************************************************************************************************
		 * Removes a card from this player's hand.
		 *
		 * cardIndex is the card that's removed. If this card slot is empty, nullptr is returned.
		 *
		 * Inputs:
		 *	m_hand:	The array of card pointers that make up the player's hand.
		 *
		 * Outputs:
		 *	Returns a pointer to the card that was removed.
		 *	m_hand: Sets the pointer for this card slot to nullptr.
		 *	m_numOfCardsInHand: Decremented if a card is removed from this hand.
		 *
		 * Exceptions:
		 *	-	Logic error if m_numOfCardsInHand indicates the hand is empty, but we found a card at the specified card slot.
		 *	-	Runtime error if we're trying to remove a card from an empty card slot.
		 *GetCard
		 * Notes:
		 ******************************************************************************************************************/
		void RemoveCardFromHand(unsigned int cardIndex);

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
		void RemoveAllCardsFromHand();

		Card *GetCard(uint cardIndex);

	signals:

	public slots:

	private:

		uint m_ID;			// Index we'll pass to the GUI to add cards to the hand
		uint m_currentNumOfCards;
		uint m_maxNumOfCards;
		uint m_cardRotation;
		Card **m_hand;					// Array of card ptrs for the cards in the hand

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
