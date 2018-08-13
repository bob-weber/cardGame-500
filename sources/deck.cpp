#include "deck.h"
#include "card.h"

unsigned int Deck::GetTotalCardCount() const
{
	return m_totalCardCount;
}

Deck::Deck(DeckType deckType, unsigned int numOfJokers, unsigned int numOfDecks, QObject *parent) : QObject(parent)
{
	// How many total cards in this deck
	m_totalCardCount = (numOfCardsPerDeck[deckType] * numOfDecks) + numOfJokers;

	if (m_totalCardCount > 0)
	{	// A non-empty deck has been specified
		// Allocate heap memory for the new deck
		try {
			m_deck = new Card*[m_totalCardCount];
		}
		catch	(exception &ex) {
			cout << "exception when allocating cards: " << ex.what() << endl;

		}

		/* Go through all possible cards. If the type of deck we're creating needs that card, allocate it.
		 * Also, if more than one deck is requested, allocate multiples of this card.
		 */
		unsigned int cardCount = 0;
		for (int pipIndex = static_cast<int>(Card::PIP_2); pipIndex <= static_cast<int>(Card::PIP_ACE); pipIndex++)
		{
			bool createCard = false;
			switch (deckType)
			{
				case	DECK_EMPTY:
					createCard = false;
					break;

				case	DECK_STANDARD:
					if ( ((pipIndex >= static_cast<int>(Card::PIP_2)) && (pipIndex <= static_cast<int>(Card::PIP_ACE)))) {
						createCard = true;
					}
					break;

				case	DECK_4S_AND_UP:
					if ( ((pipIndex >= static_cast<int>(Card::PIP_4)) && (pipIndex <= static_cast<int>(Card::PIP_10))) ||
					     ((pipIndex >= static_cast<int>(Card::PIP_JACK)) && (pipIndex <= static_cast<int>(Card::PIP_ACE)))) {
						createCard = true;
					}
					break;

				case	DECK_9S_AND_UP:
					if ( ((pipIndex >= static_cast<int>(Card::PIP_9)) && (pipIndex <= static_cast<int>(Card::PIP_10))) ||
					     ((pipIndex >= static_cast<int>(Card::PIP_JACK)) && (pipIndex <= static_cast<int>(Card::PIP_ACE)))) {
						createCard = true;
					}
					break;

				default:
					// Invalid deck specified. Logic error.
					throw invalid_argument("Unhandled deck type");
					//break;
			}

			if (createCard)
			{	// This is a card we need to add to our deck
				// Create a card for each suit
				for (int suitIndex = static_cast<int>(Card::SUIT_SPADE); suitIndex <= static_cast<int>(Card::SUIT_HEART); suitIndex++)
				{
					for (unsigned int deckCount = 0; deckCount < numOfDecks; deckCount++)
					{
						if (cardCount < m_totalCardCount)
						{	// Logic error check
							m_deck[cardCount] = new Card(static_cast<Card::Pip>(pipIndex), static_cast<Card::Suit>(suitIndex));
							cardCount++;
							//cout << "count=" << cardCount << ", pip=" << pipIndex << ", suit=" << suitIndex << endl;
						}
						else
						{	// Index is too big. Some logic error.
							throw out_of_range("Trying to create too many cards.");
						}
					}	// for each deck
				}	// for each suit
			}
			// else, not creating cards for this pip
		}	// for each pip

		if (numOfJokers > 0)
		{	// We need to add jokers
			// If we need multiple jokers, we alternate between red and black jokers.
			// For a red joker, we pretend it's a heart. For a black joker, we pretend it's a spade.
			Card::Suit suit = Card::SUIT_HEART;
			for (unsigned int jokerCount = 0; jokerCount < numOfJokers; jokerCount++)
			{
				if (cardCount < m_totalCardCount)
				{
					m_deck[cardCount] = new Card(Card::PIP_JOKER, suit);
					cardCount++;
					suit = (suit == Card::SUIT_HEART) ? Card::SUIT_SPADE : Card::SUIT_HEART;
				}
				else {
					throw out_of_range("Trying to create too many cards.");
				}
			} // for each joker
		}	// No jokers needed

		if (cardCount != m_totalCardCount)
		{	// We haven't created all the expected cards
			throw out_of_range("Created too few cards");
		}

		// Set the deck's backside image
		// This is a static class variable, so using any card will work.
		SetBackImage("blue_solid.svg");

		// Set the "no card" image
		QImage image = QImage(m_deckImageePath + "empty_card.svg");
		QSize imageSize = image.size();
		imageSize /= m_deck[0]->GetImageDivisor();
		m_noCardImage = image.scaled(imageSize);

	}
	// else, no cards needed for this deck.

	// Initialize draw index to the top of the deck
	m_drawIndex = 0;
}

Deck::~Deck()
{
	for (unsigned int i = 0; i < m_totalCardCount; i++)
	{
		delete m_deck[i];
	}
	delete[] m_deck;
}

void Deck::Shuffle()
{
	// From https://www.geeksforgeeks.org/shuffle-a-given-array/
	// Use a different seed value so that we don't get same
	// result each time we run this program
	srand(time(nullptr));

	// Start from the last element and swap one by one. We don't
	// need to run for the first element that's why i > 0
	for (int i = m_totalCardCount - 1; i >= 0; i--)
	 {
		   // Pick a random index from 0 to totalCards - 1
		   int j = rand() % (i + 1);

			 // Swap deck[i] with the element at random index
			 // cout << "swapping " << i << " with " << j << endl;
			 swap(m_deck[i], m_deck[j]);
	 }

	 // After shuffling the deck, we restart drawing from the top
	 m_drawIndex = 0;

}

Card *Deck::GetNextCard()
{
	Card *card = nullptr;
	if (m_drawIndex < m_totalCardCount)
	{
		card = m_deck[m_drawIndex];
		m_drawIndex++;
	}
	return card;
}


QImage Deck::GetBackImage() const
{
	return m_backImage;
}

void Deck::SetBackImage(QString backImage)
{
	QImage image = QImage(m_deckImageePath + backImage);
	QSize imageSize = image.size();
	imageSize /= m_deck[0]->GetImageDivisor();
	m_backImage = image.scaled(imageSize);
}

QImage Deck::GetNoCardImage() const
{
	return m_noCardImage;
}

void Deck::Print()
{
	for (unsigned int deckIndex = 0; deckIndex < m_totalCardCount; deckIndex++)
	{
		// m_deck[deckIndex]->Print();
		cout << m_deck[deckIndex]->Print() << ", ";
	}
	cout << endl;
}

