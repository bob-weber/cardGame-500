#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <QImage>

#include "card.h"

class Deck : public QObject
{
		Q_OBJECT
	public:
		// Types of decks
		typedef enum
		{
			DECK_EMPTY = 0,		// Empty deck
			DECK_STANDARD,		// Numerics 2 - 10, jacks, queens, kings and aces
			      DECK_4S_AND_UP,		// Numerics 4 - 10, jacks, queens, kings and aces
			      DECK_9S_AND_UP,		// Numerics 9 and 10, jacks, aces and kings
			DECK_TOTAL_TYPES
		} DeckType;

		// Retrieve how many cards are in the deck
		Q_PROPERTY(unsigned int totalCardCount
		           READ GetTotalCardCount)
		unsigned int GetTotalCardCount() const;

		Q_PROPERTY(QImage m_backImage
		           READ GetBackImage)
		QImage GetBackImage() const;
		void SetBackImage(QString backImage);

		Q_PROPERTY(QImage m_noCardImage
		           READ GetNoCardImage)
		QImage GetNoCardImage() const;

		/******************************************************************************************************************
		 * Constructor that creates the specified deck.
		 * Inputs:
		 *	 parent				- ParentPlayerT object. Not used.
		 * 	 type					- The type of deck to create
		 * 	 numOfJokers	-	Number of jokers to include.
		 * 	 								Decks typically have a red and black joker. Having more than 2 jokers would mean having
		 * 	 								multiples of the same joker. Presumably that's okay.
		 * 	 numOfDecks	- Can use multiple decks
		 *
		 * Outputs:
		 *   m_totalCardCount-	private variable that indicates the total # of cards in the deck.
		 *   m_deck					 - Pointer to an array of pointers that point to each card.
		 *
		 * Exceptions: invalid_argument -	The specified deck type is invalid
		 * 						 out_of_range -	There's a logic error. The code tried to create either too many or too few cards,
		 * 						 								based on the input parameters.
		 * Notes:	None
		 ******************************************************************************************************************/
		explicit Deck(DeckType type = DECK_EMPTY, unsigned int numOfJokers = 0, unsigned int numOfDecks = 1, QObject *parent = nullptr);

		/******************************************************************************************************************
		 * Destructor. Remove the deck, freeing up the memory allocated.
		 *
		 * Inputs:	None
		 *
		 * Outputs:	memory allocated to m_deck is freed up.
		 *
		 * Notes:	None
		 ******************************************************************************************************************/
		~Deck();

		/******************************************************************************************************************
		 * Shuffles the cards in the deck.
		 * Inputs:
		 *	deck		- None
		 * Outputs:	A shuffled deck
		 * Notes:
		 ******************************************************************************************************************/
		void Shuffle();

		/******************************************************************************************************************
		 * Print out the deck, using text in a console window.
		 *
		 * Inputs:
		 *	deck	-	None
		 *
		 * Outputs:	No updated variables.
		 *
		 * Notes:		This is used for debugging/inspecting the deck.
		 ******************************************************************************************************************/
		void Print();


		/******************************************************************************************************************
		 * Returns the next card to be "dealt" from the deck
		 *
		 * Inputs:
		 *	drawIndex	-	The next card to use from the deck
		 *
		 * Outputs:	No updated variables.
		 *	drawIndex	-	Advanced to the next card.
		 *	Returns a pointer to the "drawn" card.
		 *
		 * Notes:	If we're at the end of the deck, a nullptr is returned.
		 ******************************************************************************************************************/
		Card *GetNextCard();

	signals:

	public slots:

	protected:

	private:
		const unsigned int numOfCardsPerDeck[DECK_TOTAL_TYPES] =
		{	// Number of cards for the specified deck (jokers handled separately)
		    0,		// empty deck
		    52,		// Standard deck
		    44,		// 4s and up
		    24		// 9s and up
		};
		unsigned int m_totalCardCount;		// total # of cards in the combined decks

		Card **m_deck;			// The deck of cards
		unsigned int m_drawIndex;		// The index from where we're draing cards

		// Back and "no card" images. These are the same for the entire deck.
		QImage m_backImage;
		QImage m_noCardImage;
		const QString m_deckImageePath = ":/resources/cardImages/cards-compact/backs/";
//		const QString m_cardBackImagePath = ":/resources/cardImages/cards-compact/backs/blue_solid.svg";

};

#endif // DECK_H
