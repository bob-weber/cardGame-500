#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "headers/card.h"

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

		void SetCardOrientation(uint cardId, Card::Orientation orientation);

		void ToggleCardSelection(Card* card);

		void DeselectAllCards();

		void SwapCards(uint cardId, Player* player2, uint player2cardId);

		Card *GetCard(uint cardIndex);
		void SetCard(uint cardIndex, Card* card);

	signals:
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
