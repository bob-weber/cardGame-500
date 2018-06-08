#include "deck.h"
#include "player.h"

#include "gamelogic_500.h"

using namespace std;

gameLogic_500::gameLogic_500(QObject *parent) : QObject(parent)
{

}

gameLogic_500::~gameLogic_500()
{
	// Delete players
	for (uint i = 0; i < m_numOfHands; i++)
	{
		delete m_player[i];
	}
	delete[] m_player;
}

void gameLogic_500::PlayGame()
{
	// bool gameOver = false;

	// Create a deck
	deck = new Deck(Deck::DECK_4S_AND_UP, 1, 1);
	deck->Print();

	// Instantiate the players
	m_player = new Player *[m_numOfHands];
	for (uint playerIndex = 0; playerIndex < m_numOfHands; playerIndex++)
	{
		m_player[playerIndex] = new Player();

		// Set each player's ID
		m_player[playerIndex]->SetID(m_PlayerInfo[playerIndex].GUI_ID);

		// All players start of with no cards
		m_player[playerIndex]->SetCurrentNumOfCards(0);

		// Max # of cards depends on whether this is a normal player or the kitty
		m_player[playerIndex]->SetMaxNumOfCards(m_PlayerInfo[playerIndex].maxNumOfCards);

		if (playerIndex < m_KittyID)
		{	// Not the kitty
			// Update the player's GUI name
			emit PlayerNameChanged(m_PlayerInfo[playerIndex].GUI_ID, m_PlayerInfo[playerIndex].name);
			emit PlayerActionChanged(m_PlayerInfo[playerIndex].GUI_ID, "Wait");
		}
	}

	//emit finished();
}

void gameLogic_500::ReturnAllCards()
{
	// Return all cards from the players and the kitty
	for (uint playerIndex = 0; playerIndex < m_numOfHands; playerIndex++)
	{
		m_player[playerIndex]->RemoveAllCardsFromHand();
	}
}

void gameLogic_500::Deal()
{
	ReturnAllCards();
	deck->Shuffle();

	// Deal all cards
	// 10 go to each player, and 5 to the kitty.
	uint playerIndex = 0;
	bool dealToKittyThisPass = false;
	for (uint cardIndex = 0; cardIndex < deck->GetTotalCardCount(); cardIndex++)
	{
		AddCardToPlayer(m_player[playerIndex]);
		++playerIndex;

		// Reset the player index when appropriate
		if (dealToKittyThisPass)
		{	// Don't reset player index until we deal to the kitty
			if (playerIndex >= m_numOfHands)
			{
				playerIndex = 0;
				dealToKittyThisPass = false;
			}
			// Deal to next player or kitty
		}
		else
		{	// Don't deal a card to the kitty, so reset 1 less than # of hands
			if (playerIndex >= (m_numOfHands - 1))
			{
				playerIndex = 0;
				dealToKittyThisPass = true;
			}
			// Deal to next player
		}
	}
}

void gameLogic_500::CardClicked(uint player, uint card)
{
	Card *playerCard = nullptr;
	// Find the player that matches our player index
	for (uint playerIndex = 0; playerIndex < m_numOfHands; playerIndex++)
	{
		if (m_player[playerIndex]->GetID() == player)
		{	// This is the player who's card was clicked
			playerCard = m_player[playerIndex]->GetCard(card);
			break;
		}
		// else, not the correct player
	}	// for

	if (playerCard != nullptr)
	{	// We have a valid card
		Card::Orientation orientation = playerCard->FlipOrientation();
		if (orientation == Card::FACE_DOWN) {
			PlayerCardChanged(player, card, playerCard->GetBackImage());
		}
		else {
			PlayerCardChanged(player, card, playerCard->GetFaceImage());
		}
	}
	// else, this card hasn't been dealt yet or we didn't find it
}

void gameLogic_500::AddCardToPlayer(Player *player)
{
	//cout << "player=" << playerIndex << ", card=" << cardIndex << endl;

	// Get the next card in the deck and add it to this player's hand.
	Card *card = deck->GetNextCard();
	uint handIndex = player->AddCardToHand(card);

	if (handIndex < player->GetMaxNumOfCards())
	{	// We successfully added the card to this player's hand
		QImage image;
		if (card->GetOrientation() == Card::FACE_DOWN) {
			image = card->GetBackImage();
		}
		else {
			image = card->GetFaceImage();
		}
		// Update the GUI with this card.
		emit PlayerCardChanged(player->GetID(), handIndex, image);
	}
	else
	{
		throw out_of_range("gameLogic_500::AddCardToPlayer: Couldn't add card to player.");
	}
}
