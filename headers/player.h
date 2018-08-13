#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "card.h"
#include "bid.h"

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
		 * Gets/sets the specified card's orientation, or flips it.
		 *
		 * Inputs:
		 *	 cardPos:			The position of the card in the player's hand
		 *	 orientation:	The orientation to set the card to.
		 *
		 * Outputs:
		 *	m_hand:	The specified card in the hand has it's orientation field udpated.
		 *
		 * Notes:
		 *   1. Emits a signal to update the GUI
		 ******************************************************************************************************************/
		Card::Orientation GetCardOrientation(uint cardPos) const;
		void SetCardOrientation(uint cardPos, Card::Orientation orientation);
		void FlipCardOrientation(uint cardPos);

		/******************************************************************************************************************
		 * This is a convenience function that sets the specified orientation for all cards in a player's hand.
		 *
		 * Inputs:
		 *	 orientation:	The card we want to select or deselect.
		 *
		 * Outputs:
		 *	 m_hand[].orientaiton:	Card's orientation is updated.
		 ******************************************************************************************************************/
		void SetHandOrietation(Card::Orientation orientation);

		/******************************************************************************************************************
		 * Gets/sets the specified card's selection, or toggles it.
		 *
		 * Inputs:
		 *	 cardPos:			The position of the card in the player's hand
		 *	 isSelected:	When the card is/should be selected.
		 *
		 * Outputs:
		 *	 m_hand:	The specified card in the hand has it's orientation field udpated.
		 *
		 * Notes:
		 *   SetCardSelection emits a signal to update the GUI
		 *   Using that function or ToggleCardSelection will result in a count of the number of selected cards being
		 *   maintained, and the GUI being updated.
		 *   ONLY USE THESE FUNCTINOS to change a card's selection.
		 ******************************************************************************************************************/
		bool IsCardSelected(uint cardPos) const;
		void SetCardSelection(uint cardPos, bool isSelected);
		void ToggleCardSelection(uint cardPos);

		/******************************************************************************************************************
		 * A convenience function that deslects all cards. and zeroes out the player's selected card counter.
		 * A signal is emitted to update the GUI for each card.
		 *
		 * Inputs:
		 *	 m_hand:	Cards in the player's hand are all deselected.
		 *
		 * Outputs:
		 *	 m_hand[].isSelected:	 The card's selection status.
		 *	 m_numOfSelectedCards: Reset to 0. This shouldn't be necessary if the counter is maintained properly, but it
		 *                         may be a good idea to reset it when we know it's 0.
		 ******************************************************************************************************************/
		void DeselectAllCards();

		/******************************************************************************************************************
		 * Counts how many cards are in the hand for each suit. This helps the game logic determine what plays are valid.
		 *
		 * Inputs:
		 *	 trumpSuit:	The suit of trump. This determines which suit the jacks are counted under.
		 *
		 * Outputs:
		 *	m_numOfSuits[], an array of counters for each suit, is updated.
		 *
		 * Notes:
		 *	- This function is not run automatically after cards are dealt or merged. It's up to the game logic to call
		 *		this function before starting play for a hand.
		 ******************************************************************************************************************/
		void CountSuits(Bid::bidSuitT trumpSuit);

		/******************************************************************************************************************
		 * Returns the number of cards of the specified suit in the player's hand.
		 *
		 * Inputs:
		 *	 suit:	The suit to check
		 *
		 * Outputs:
		 *	 Returns the number of cards in the players hand of the specified suit.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		uint GetSuitCount(Card::Suit suit);

		/******************************************************************************************************************
		 * Determines the suit of a card, which can be different that the card's printed suit due to the trump suit and
		 * bowers.
		 *
		 * Inputs
		 *	 card:	The card to determine the suit for.
		 *   trumpSuit:	The trump suit for this hand.
		 *
		 * Outputs
		 *	 Returns the card's suit after taking the bid into consideration.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		Card::Suit GetTrumpSuit(Card *card, Bid::bidSuitT trumpSuit);

		/******************************************************************************************************************
		 * Sorts the cards in a player's hand. It retrieves the "sort value" of each card, and swaps them so they are
		 * in increasing order. The sorting is done in place.
		 *
		 * Inputs:
		 *	 m_hand[]:	The player's hand of cards.
		 *
		 * Outputs:
		 *	m_hand[] is updated.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void SortHand();

		/******************************************************************************************************************
		 * Updates the table GUI for the given hand. This is hand after you've manipulated the cards, say with sorting,
		 * and didn't update after each card change.
		 *
		 * The design approach is to always update the table through Player, since this class knows where each card is
		 * located. Don't change a card's oritation, selection or card through the Card class, only this Player class.
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

		/******************************************************************************************************************
		 * Adds a card to this player's hand. It verifies there's room in the hand, and if so, searches for an empty
		 * location to place the card.
		 *
		 * If the hand is full, a runtime exception is thrown.
		 *
		 * Inputs:
		 *	 card:	The card to add to the hand.
		 *   orientation: Whether to set the card face up or face down.
		 *
		 * Outputs:
		 *	 Returns the index into the player's hand to which the card was added.
		 *	 if no empty slot is found, returns m_MaxNumOfCardsInHand, which is an invalid index.
		 *
		 *   Updates the cards position in m_hand[].
		 *
		 * Exceptions:
		 *	- Throws a logic error if m_numOfCardsInHand indicates there's an empty card slot, but we cannot find one in
		 *		the hand.
		 *	-	Throws a runtime error if we have no room in the hand for the new card.
		 * Notes:
		 ******************************************************************************************************************/
		uint AddCard(Card *card, Card::Orientation orientation);

		/******************************************************************************************************************
		 * Clears all cards from the hand. This means we set all card pointers to null.
		 *
		 * Inputs:	None
		 *
		 * Outputs:
		 *	m_hand:	The array of card pointers that make up the player's hand are set to null.
		 *	m_numOfCardsInHand: Cleared tSetCardOrientationo 0, since we've turned in all of the cards.
		 *
		 * Exceptions:
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void RemoveAllCards();

		/******************************************************************************************************************
		 * Get/set a card in the player's hand.
		 *
		 * Inputs:
		 *	 cardIndex:	The card in the hand to set or get.
		 *	 card: When setting, the card to set.
		 *
		 * Outputs:
		 *	 m_hand[] is updated.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		Card *GetCard(uint cardIndex);
		void SetCard(uint cardIndex, Card* card);

		/******************************************************************************************************************
		 * Swaps 2 cards between 2 player's hands, this player, and player2.
		 *
		 * Inputs:
		 *	 cardId:				The card in the player's hand to swap
		 *   player2:				The other player to swap with
		 *   player2CardId:	The card in the 2nd player's hand to swap
		 *
		 * Outputs:
		 *	m_hand[].card:	Each player's hand is updated.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void SwapCards(uint cardId, Player* player2, uint player2cardId);

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

		uint m_playerId;				// Id of this player
		uint m_teamId;					// Which team this player belongs to
		QString m_playerName;		// Player name
		uint m_currentNumOfCards;	// Number of cards in the player's hand
		uint m_maxNumOfCards;			// Max number of cards this player can have
		uint m_cardRotation;			// Rotation of the card
		uint m_numOfSelectedCards;	// Num of cards selected. This is useful for some of the game logic.
		uint m_numOfSuits[Card::SUIT_NUMBER_OF_SUITS];	// How many cards of each suit

		/* For each card position on the table, we need to know what card,
		 * It's orientation, and selection.
		 */
		typedef struct
		{
			bool isSelected;
			Card::Orientation orientation;
			Card* card;
		} HandT;
		HandT m_hand[NUM_OF_CARDS_PER_PLAYER];
};

#endif // PLAYER_H
