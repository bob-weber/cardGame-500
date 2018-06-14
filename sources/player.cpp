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
	Card *card = nullptr;
	if (m_hand[cardIndex] != nullptr)
	{	// This card slot is not empty
		card = m_hand[cardIndex];
		m_hand[cardIndex] = nullptr;
		if (m_currentNumOfCards > 0)
		{
			--m_currentNumOfCards;
		}
		else
		{
			throw logic_error("RemoveCardFromHand: m_numOfCardsInHand is 0, but we found a card in the hand.");
		}
	}
	else
	{
		throw runtime_error("RemoveCardFromHand: Trying to remove a card from an empty card slot.");
	}
}

void Player::RemoveAllCardsFromHand()
{
	for (unsigned int cardIndex = 0; cardIndex < m_maxNumOfCards; ++cardIndex)
	{
		m_hand[cardIndex] = nullptr;
	}
	m_currentNumOfCards = 0;
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
