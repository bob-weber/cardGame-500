#include "game_500_settings.h"
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

	/* Initialize all card ptrs to null. Even though not all players use NUM_OF_CARDS_PER_PLAYER cards,
	 * we still initialize all available entries to null.
	 */
	for (uint cardPos = 0; cardPos < NUM_OF_CARDS_PER_PLAYER; cardPos++)
	{
		m_hand[cardPos].card = nullptr;
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
	for (uint cardPos = 0; cardPos < m_maxNumOfCards; cardPos++)
	{
		emit CardChanged(m_playerId, cardPos);
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

Card::Orientation Player::GetCardOrientation(uint cardPos) const
{
	Card::Orientation orientation = Card::FACE_DOWN;
	if (m_hand[cardPos].card != nullptr)
	{
		orientation = m_hand[cardPos].orientation;
	}
	// else, no card at this position. Ignore.
	return orientation;
}

void Player::SetCardOrientation(uint cardPos, Card::Orientation orientation)
{
	if (m_hand[cardPos].card != nullptr)
	{	// not an empty slot
		if (m_hand[cardPos].orientation != orientation)
		{
			m_hand[cardPos].orientation = orientation;
			emit CardChanged(m_playerId, cardPos);
		}
		// else, orientation hasn't changed
	}
	// else, no card at this position. Ignore.
}

void Player::FlipCardOrientation(uint cardPos)
{
	if (m_hand[cardPos].card != nullptr)
	{
		Card::Orientation orientation = (m_hand[cardPos].orientation == Card::FACE_DOWN) ? Card::FACE_UP : Card::FACE_DOWN;
		SetCardOrientation(cardPos, orientation);
	}
	// else, no card at this position. Ignore.
}

void Player::SetHandOrietation(Card::Orientation orientation)
{
	for (uint cardPos = 0; cardPos < m_maxNumOfCards; cardPos++)
	{
		Card* card = m_hand[cardPos].card;
		if (card != nullptr)
		{
			m_hand[cardPos].orientation = orientation;
			emit CardChanged(m_playerId, cardPos);
		}
	}
}

bool Player::IsCardSelected(uint cardPos) const
{
	bool isSelected = false;
	if (m_hand[cardPos].card != nullptr)
	{
		isSelected = m_hand[cardPos].isSelected;
	}
	// else, no card at this position. Ignore.
	return isSelected;
}

void Player::SetCardSelection(uint cardPos, bool isSelected)
{
	if (m_hand[cardPos].card != nullptr)
	{	// not an empty slot
		if (m_hand[cardPos].isSelected != isSelected)
		{	// Change in card selection
			m_hand[cardPos].isSelected = isSelected;
			if (isSelected) {
				++m_numOfSelectedCards;
			}
			else {
				--m_numOfSelectedCards;
			}
			emit CardChanged(m_playerId, cardPos);
		}
	}
	// else, no card at this position. Ignore.
}

void Player::ToggleCardSelection(uint cardPos)
{
	bool selected = false;
	if (m_hand[cardPos].card != nullptr)
	{
		selected = !m_hand[cardPos].isSelected;
		m_hand[cardPos].isSelected = selected;
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
	for (unsigned int cardPos = 0; cardPos < m_maxNumOfCards; ++cardPos)
	{
		SetCardSelection(cardPos, false);
	}
	m_numOfSelectedCards = 0;
}

void Player::CountSuits(Bid::bidSuitT trumpSuit)
{
	// Zero all the suit counts
	for (auto suitId = 0; suitId < Card::SUIT_NUMBER_OF_SUITS; suitId++)
	{
		m_numOfSuits[suitId] = 0;
	}

	for (uint cardPos = 0; cardPos < NUM_OF_CARDS_PER_PLAYER; cardPos++)
	{
		Card* card = m_hand[cardPos].card;
		if (card != nullptr)
		{

			// Increment the count for the found suit
			auto cardSuit = GetTrumpSuit(card, trumpSuit);
			m_numOfSuits[cardSuit]++;
		}
	}
}

uint Player::GetSuitCount(Card::Suit suit)
{
	return m_numOfSuits[suit];
}

Card::Suit Player::GetTrumpSuit(Card* card, Bid::bidSuitT trumpSuit)
{
	/* Determine the card suit. Start with the actual suit of the card, and then
	 * check for reasons we might override this suit (bowers, jokers).
	 */
	auto cardSuit = card->GetSuit();
	auto cardPip = card->GetPip();

	/* Handle bowers
	 * 1. If we have a red trump, both red jacks are the suit of that trump.
	 * 2. If we have a black trump, both black jacks are the suit of that trump.
	 * Handle jokers
	 * 1. A joker is the same suit as the trump suit for normal suit bids.
	 * 2. For no trump and nellow bids, it doesn't affect the suit.
	 * 3. Note: The suit specified in Card for the joker is a heart, but it's not really
	 *    a heart. We'll not count it as a heart unless hearts are trump.
	 */
	switch (trumpSuit)
	{
		case Bid::BID_SPADES:
			if ( ( (cardPip == Card::PIP_JACK) &&
			       ((cardSuit == Card::SUIT_SPADE) || (cardSuit == Card::SUIT_CLUB)) ) ||
			     (cardPip == Card::PIP_JOKER) )
			{
				cardSuit = Card::SUIT_SPADE;
			}
			break;

		case Bid::BID_CLUBS:
			if ( ( (cardPip == Card::PIP_JACK) &&
			       ((cardSuit == Card::SUIT_SPADE) || (cardSuit == Card::SUIT_CLUB)) ) ||
			     (cardPip == Card::PIP_JOKER) )
			{
				cardSuit = Card::SUIT_CLUB;
			}
			break;

		case Bid::BID_DIAMONDS:
			if ( ( (cardPip == Card::PIP_JACK) &&
			       ((cardSuit == Card::SUIT_DIAMOND) || (cardSuit == Card::SUIT_HEART)) ) ||
			     (cardPip == Card::PIP_JOKER) )
			{
				cardSuit = Card::SUIT_DIAMOND;
			}
			break;

		case Bid::BID_HEARTS:
			if ( ( (cardPip == Card::PIP_JACK) &&
			       ((cardSuit == Card::SUIT_DIAMOND) || (cardSuit == Card::SUIT_HEART)) ) ||
			     (cardPip == Card::PIP_JOKER) )
			{
				cardSuit = Card::SUIT_HEART;
			}
			break;

		default:
			// Bids of no trump or a type of nellow do not result in changes to the card's suit.
			break;
	}

	return cardSuit;
}

void Player::SortHand()
{
	PrintHand();
	for (uint i = 0; i < m_maxNumOfCards-1; i++)
	{
		for (uint j = i+1; j < m_maxNumOfCards; j++)
		{
			Card* card1 = m_hand[i].card;
			Card* card2 = m_hand[j].card;
			if ((card1 != nullptr) && (card2 != nullptr))
			{
				if (card1->GetSortValue() > card2->GetSortValue())
				{	// Swap these 2 cards
					SwapCards(i, this, j);
				}
				// else, cards are in correct order. Don't swap.
			}
		}
	}
	PrintHand();
}


void Player::RefreshHand()
{
	/* Note: Typically, we'd refresh the max # of cards for this player: m_maxNumOfCards
	 * This is 10 for normal players, 5 for the kitty.
	 * However, while the kitty will only have 5 cards, it's also used as the playing area,
	 * and when used in that way (while playing cards), we need to refresh all kitty entries.
	 * So, we always refresh all possible table positions in the kitty, and the players.
	 */
	for (uint cardPos = 0; cardPos < NUM_OF_CARDS_PER_PLAYER; cardPos++)
	{
		emit CardChanged(m_playerId, cardPos);
	}
}

void Player::PrintHand()
{
	cout << m_playerName.toStdString() << ": ";
	for (uint cardPos = 0; cardPos < m_maxNumOfCards; cardPos++)
	{
		Card* card = m_hand[cardPos].card;
		cout << card->Print() << ", ";
	}
	cout << endl;
}

uint Player::AddCard(Card *card, Card::Orientation orientation)
{
	uint cardPos = m_maxNumOfCards;	// This is an invalid index value. We'll set it to a valid one if successful.

	if (m_currentNumOfCards < m_maxNumOfCards)
	{	// We have room in the hand for another card
		cardPos = FindEmptyHandSlot();
		if (cardPos < m_maxNumOfCards)
		{	// We found an entry to deal the card
			m_hand[cardPos].card = card;
			m_hand[cardPos].orientation = orientation;
			m_hand[cardPos].isSelected = false;
			++m_currentNumOfCards;

			emit CardChanged(m_playerId, cardPos);
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
	return cardPos;
}

void Player::RemoveAllCards()
{
	for (unsigned int cardPos = 0; cardPos < m_maxNumOfCards; ++cardPos)
	{
		if (m_hand[cardPos].card != nullptr)
		{	// This is a valid card
			m_hand[cardPos].card = nullptr;

			// Update the card image before deleting the card, so we have an image on the table.
			// TODO: Update image on table with a transparent card image when there is no card.
			emit CardChanged(m_playerId, cardPos);

			m_hand[cardPos].card = nullptr;
			if (m_currentNumOfCards > 0) {
				--m_currentNumOfCards;
			}
		}
	}
}

Card *Player::GetCard(uint cardIndex)
{
	return m_hand[cardIndex].card;
}

void Player::SetCard(uint cardIndex, Card *card)
{
	m_hand[cardIndex].card = card;
}

void Player::SwapCards(uint cardPos, Player* player2, uint player2CardPos)
{
	Card* tempCard = GetCard(cardPos);
	SetCard(cardPos, player2->GetCard(player2CardPos));
	player2->SetCard(player2CardPos, tempCard);
}

unsigned int Player::FindEmptyHandSlot()
{
	unsigned int emptySlot = m_maxNumOfCards;
	for (unsigned int cardPos = 0; cardPos < m_maxNumOfCards; cardPos++)
	{
		if (m_hand[cardPos].card == nullptr)
		{	// open slot
			emptySlot = cardPos;
			break;		// Found a location
		}
	}

	return emptySlot;
}
