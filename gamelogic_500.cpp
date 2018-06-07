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
	for (uint i = 0; i < m_numOfPlayers; i++)
	{
		delete m_player[i];
	}
	delete[] m_player;

	// Delete the kitty
	delete m_kitty;

}

void gameLogic_500::PlayGame()
{
	bool gameOver = false;

	// Create a deck
	deck = new Deck(Deck::DECK_4S_AND_UP, 1, 1);
	deck->Print();

	// Instantiate the players
	m_player = new Player *[m_numOfPlayers];
	for (uint i = 0; i < m_numOfPlayers; i++)
	{
		m_player[i] = new Player(i, m_numOfCardsPerPlayer);
	}

	// Create the kitty
	// The kitty player index is 4. This is defined by the GUI.
	m_kitty = new Player(4, m_numOfCardsInKitty);

	// set the player's names
	emit PlayerNameChanged(0, "Kathy");
	emit PlayerNameChanged(1, "Theodore");
	emit PlayerNameChanged(2, "Priya");
	emit PlayerNameChanged(3, "Edward");
	emit PlayerActionChanged(0, "Wait");
	emit PlayerActionChanged(1, "Wait");
	emit PlayerActionChanged(2, "Wait");
	emit PlayerActionChanged(3, "Wait");
#if 0
	while (!gameOver)
	{
		//gameOver = true;
	}	// while
#endif

	//emit finished();
}

void gameLogic_500::ReturnAllCards()
{
	// Return all cards from the players and the kitty
	for (uint playerIndex = 0; playerIndex < m_numOfPlayers; playerIndex++)
	{
		m_player[playerIndex]->RemoveAllCardsFromHand();
	}
	m_kitty->RemoveAllCardsFromHand();	// Empty the kitty

}

void gameLogic_500::Deal()
{
	ReturnAllCards();
	deck->Shuffle();

	// Deal all cards
	// 10 go to each player, and 5 to the kitty.
	uint playerIndex = 0;
	bool dealToKittyThisPass = false;
	for (uint cardIndex = 0; cardIndex < deck->getTotalCardCount(); cardIndex++)
	{
		if (playerIndex < m_numOfPlayers)
		{	// Deal to a player's hand
			AddCardToPlayer(m_player[playerIndex]);
		}
		else
		{	// We're dealing to the kitty
			AddCardToPlayer(m_kitty);
		}
		++playerIndex;

		// Reset the player index when appropriate
		if (dealToKittyThisPass)
		{	// Don't reset player index until we deal to the kitty
			if (playerIndex >= (m_numOfPlayers + 1))
			{
				playerIndex = 0;
				dealToKittyThisPass = false;
			}
			// Deal to next player or kitty
		}
		else
		{	// Don't deal a card to the kitty
			if (playerIndex >= m_numOfPlayers)
			{
				playerIndex = 0;
				dealToKittyThisPass = true;
			}
			// Deal to next player
		}
	}
}

void gameLogic_500::AddCardToPlayer(Player *player)
{
	//cout << "player=" << playerIndex << ", card=" << cardIndex << endl;

	// Get the next card in the deck and add it to this player's hand.
	Card *card = deck->GetNextCard();
	uint handIndex = player->AddCardToHand(card);

	if (handIndex < player->getPlayerMaxCards())
	{	// We successfully added the card to this player's hand
		// Update the GUI with this card.
		// Scale images to 1/4 their size. TODO: Make this adjustable based on table size.
		const float imageScalingDivisor = 4.0;
		QImage image = card->getCardImage();
		QSize imageSize = image.size() / imageScalingDivisor;
		// QSize imageScaled = imageSize / imageScalingDivisor;
		QImage imageScaled = image.scaled(imageSize);
		emit PlayerCardChanged(player->getPlayerIndex(), handIndex, imageScaled);
	}
	else
	{
		throw out_of_range("gameLogic_500::AddCardToPlayer: Couldn't add card to player.");
	}
}
