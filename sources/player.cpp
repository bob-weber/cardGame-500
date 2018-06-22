#include "card.h"
#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
}

Player::~Player()
{
	// delete card pointers
	delete[] m_hand;

}

void Player::SetID(uint ID)
{
	this->m_ID = ID;
}

uint Player::GetID() const
{
	return this->m_ID;
}

uint Player::GetMaxNumOfCards() const
{
	return this->m_maxNumOfCards;
}

void Player::SetMaxNumOfCards(uint numOfCards)
{
	this->m_maxNumOfCards = numOfCards;

	// Now that we know how many cards we have,	allocate an array of cards
	// Initialize them all to null, as no cards have been dealt yet.
	this->m_hand = new Card *[m_maxNumOfCards];
	for (uint cardIndex = 0; cardIndex < m_maxNumOfCards; cardIndex++)
	{
		m_hand[cardIndex] = nullptr;
	}
}

uint Player::GetCurrentNumOfCards() const
{
	return this->m_currentNumOfCards;
}

void Player::SetCurrentNumOfCards(uint numOfCards)
{
	this->m_currentNumOfCards = numOfCards;
}

uint Player::GetCardRotation() const
{
	return this->m_cardRotation;
}

void Player::SetCardRotation(uint rotation)
{
	this->m_cardRotation = rotation;
}

uint Player::AddCardToHand(Card *card)
{
	uint cardIndex = m_maxNumOfCards;	// This is an invalid index value. We'll set it to a valid one if successful.

	if (m_currentNumOfCards < m_maxNumOfCards)
	{	// We have room in the hand for another card
		cardIndex = FindEmptyHandSlot();
		if (cardIndex < m_maxNumOfCards)
		{	// We found an entry to deal the card
			m_hand[cardIndex] = card;
			++m_currentNumOfCards;
		}
		else
		{	// Logic error. Our card pointers and num of cards in the hand are out of sync.
			throw logic_error("AddCardToHand: m_numOfCardsInHand indicates there's room in the hand, but cannot find an empty card slot.");
		}
	}
	else
	{	// no room to deal another card to this player
		throw runtime_error("AddCardToHand: Trying to add too many cards to the hand.");
	}

	// return the location in the hand we added the card to
	return cardIndex;
}

void Player::RemoveCardFromHand(unsigned int cardIndex)
{
	if (m_hand[cardIndex] != nullptr)
	{	// This card slot is not empty
		m_hand[cardIndex]->SetOrientation(Card::FACE_DOWN);	// Flip all cards face down
		m_hand[cardIndex] = nullptr;		// Empty this place in the hand
		if (m_currentNumOfCards > 0)
		{	// Update # of cards in hand
			--m_currentNumOfCards;
		}
		else
		{
			throw logic_error("RemoveCardFromHand: m_numOfCardsInHand is 0, but we found a card in the hand.");
		}
	}
	// else, this slot is already empty
	// This is normal. We don't make sure the slot has a card before trying to remove it.
}

void Player::RemoveAllCardsFromHand()
{
	for (unsigned int cardIndex = 0; cardIndex < m_maxNumOfCards; ++cardIndex)
	{
		RemoveCardFromHand(cardIndex);
	}
	if (m_currentNumOfCards != 0)
	{	// This is an error. Counter should be maintained as we add or remove cards
		throw logic_error("RemoveAllCardsFromHand: m_numOfCardsInHand is not 0.");
	}
}


Card *Player::GetCard(uint cardIndex)
{
	return m_hand[cardIndex];
}

unsigned int Player::FindEmptyHandSlot()
{
	unsigned int emptySlot = m_maxNumOfCards;
	for (unsigned int handIndex = 0; handIndex < m_maxNumOfCards; handIndex++)
	{
		if (m_hand[handIndex] == nullptr)
		{	// open slot
			emptySlot = handIndex;
			break;		// Found a location
		}
	}

	return emptySlot;
}
