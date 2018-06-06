#include "card.h"
#include "player.h"

Player::Player(unsigned int maxCards, QObject *parent) : QObject(parent)
{
	m_numOfCardsInHand = 0;

	// Create an array of Card ptrs, to keep track of the cards in the hand
	m_maxNumOfCardsInHand = maxCards;
	m_hand = new Card *[m_maxNumOfCardsInHand];
	for (unsigned int i = 0; i < m_maxNumOfCardsInHand; i++)
	{
		m_hand[i] = nullptr;
	}
}

Player::~Player()
{
	// delete card pointers
	delete[] m_hand;

}

void Player::AddCardToHand(Card *card)
{
	if (m_numOfCardsInHand < m_maxNumOfCardsInHand)
	{	// We have room in the hand for another card
		unsigned int handIndex = FindEmptyHandSlot();
		if (handIndex < m_maxNumOfCardsInHand)
		{	// We found an entry to deal the card
			m_hand[handIndex] = card;
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
}

void Player::RemoveCardFromHand(unsigned int cardIndex)
{
	Card *card = nullptr;
	if (m_hand[cardIndex] != nullptr)
	{	// This card slot is not empty
		card = m_hand[cardIndex];
		m_hand[cardIndex] = nullptr;
		if (m_numOfCardsInHand > 0)
		{
			--m_numOfCardsInHand;
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
	for (unsigned int cardIndex = 0; cardIndex < m_maxNumOfCardsInHand; ++cardIndex)
	{
		m_hand[cardIndex] = nullptr;
	}
	m_numOfCardsInHand = 0;
}

unsigned int Player::FindEmptyHandSlot()
{
	unsigned int emptySlot = m_maxNumOfCardsInHand;
	for (unsigned int handIndex = 0; handIndex < m_maxNumOfCardsInHand; handIndex++)
	{
		if (m_hand[handIndex] == nullptr)
		{	// open slot
			emptySlot = handIndex;
			break;		// Found a location
		}
	}

	return emptySlot;
}
