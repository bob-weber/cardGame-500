#include "card.h"
#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
}

Player::~Player()
{
}

uint Player::GetPlayerId() const
{
	return this->m_playerId;
}

void Player::SetPlayerId(uint Id)
{
	this->m_playerId = Id;
}

uint Player::GetTeamId() const {
	return this->m_teamId;
}

void Player::SetTeamId(uint Id) {
	this->m_teamId = Id;
}

QString Player::GetPlayerName() {
	return this->m_playerName;
}

void Player::SetPlayerName(QString name) {
	this->m_playerName = name;
}

uint Player::GetMaxNumOfCards() const {
	return this->m_maxNumOfCards;
}

void Player::SetMaxNumOfCards(uint numOfCards) {
	this->m_maxNumOfCards = numOfCards;

	// Now that we know how many cards we have,	allocate an array of cards
	// Initialize them all to null, as no cards have been dealt yet.
	this->m_hand = new Card *[m_maxNumOfCards];
	for (uint cardIndex = 0; cardIndex < m_maxNumOfCards; cardIndex++)
	{
		m_hand[cardIndex] = nullptr;
	}
}

uint Player::GetCurrentNumOfCards() const {
	return this->m_currentNumOfCards;
}

void Player::SetCurrentNumOfCards(uint numOfCards)
{
	m_currentNumOfCards = numOfCards;
}

uint Player::GetCardRotation() const {
	return this->m_cardRotation;
}

void Player::SetCardRotation(uint rotation) {
	this->m_cardRotation = rotation;
	// Notify the GUI that all cards orientation has changed
	for (uint cardIndex = 0; cardIndex < m_maxNumOfCards; cardIndex++)
	{
		emit CardChanged(m_playerId, cardIndex);
	}
}

uint Player::GetNumOfSelectedCards() const
{
	return this->m_numOfSelectedCards;;
}

void Player::SetNumOfSelectedCards(uint numOfSelectedCards)
{
	m_numOfSelectedCards = numOfSelectedCards;
}

void Player::SetCardOrientation(uint cardId, Card::Orientation orientation)
{
	Card *card = GetCard(cardId);
	if (card != nullptr)
	{
		card->SetOrientation(orientation);
		emit CardChanged(m_playerId, cardId);
	}
	// else, invalid card
}

uint Player::AddCard(Card *card)
{
	uint cardIndex = m_maxNumOfCards;	// This is an invalid index value. We'll set it to a valid one if successful.

	if (m_currentNumOfCards < m_maxNumOfCards)
	{	// We have room in the hand for another card
		cardIndex = FindEmptyHandSlot();
		if (cardIndex < m_maxNumOfCards)
		{	// We found an entry to deal the card
			m_hand[cardIndex] = card;
			++m_currentNumOfCards;

			emit CardChanged(m_playerId, cardIndex);
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

void Player::RemoveAllCards()
{
	for (unsigned int cardIndex = 0; cardIndex < m_maxNumOfCards; ++cardIndex)
	{
		if (m_hand[cardIndex] != nullptr)
		{	// This is a valid card
			m_hand[cardIndex]->SetOrientation(Card::FACE_DOWN);	// Flip all cards face down
			m_hand[cardIndex]->SetSelected(false);

			// Update the card image before deleting the card, so we have an image on the table.
			// TODO: Update image on table with a transparent card image when there is no card.
			emit CardChanged(m_playerId, cardIndex);

			m_hand[cardIndex] = nullptr;
			if (m_currentNumOfCards > 0) {
				--m_currentNumOfCards;
			}
		}
	}
}

void Player::ToggleCardSelection(Card* card)
{
	bool selected = false;
	if (card != nullptr)
	{
		selected = !card->IsSelected();
		card->SetSelected(selected);
	}
	// Update the card seletion count
	if (selected) {
		++m_numOfSelectedCards;
	}
	else {
		--m_numOfSelectedCards;
	}
}

void Player::DeselectAllCards()
{
	for (unsigned int cardIndex = 0; cardIndex < m_maxNumOfCards; ++cardIndex)
	{
		if (m_hand[cardIndex] != nullptr)
		{	// This is a valid card
			m_hand[cardIndex]->SetSelected(false);
			emit CardChanged(m_playerId, cardIndex);
		}
	}
	m_numOfSelectedCards = 0;
}

void Player::SwapCards(uint cardId, Player* player2, uint player2cardId)
{
	Card* tempCard = GetCard(cardId);
	SetCard(cardId, player2->GetCard(player2cardId));
	player2->SetCard(player2cardId, tempCard);
	emit CardChanged(m_playerId, cardId);
	emit CardChanged(player2->GetPlayerId(), player2cardId);
}

Card *Player::GetCard(uint cardIndex)
{
	return m_hand[cardIndex];
}

void Player::SetCard(uint cardIndex, Card *card)
{
	m_hand[cardIndex] = card;
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
