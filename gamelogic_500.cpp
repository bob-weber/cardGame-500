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
		m_player[i] = new Player(m_numOfCardsPerPlayer);
	}

	// Create the kitty
	m_kitty = new Player(m_numOfCardsInKitty);

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

	// Deal 10 cards to each player, one at a time. Every other deal, add one to the kitty.
	for (uint cardIndex = 0; cardIndex < m_numOfCardsPerPlayer; cardIndex++)
	{
		for (uint playerIndex = 0; playerIndex < m_numOfPlayers; playerIndex++)
		{
			Card *card = deck->GetNextCard();
			m_player[playerIndex]->AddCardToHand(card);
			QImage image = card->getCardImage();
			QSize imageSize = image.size();
			QSize imageScaled = imageSize / 4;
			QImage cropped = image.scaled(imageScaled); // ) (copy(0, 0, 40, 40);
			//QRect imageRect(0, 0, 40, 40);
			//QPixmap croppedImage = image.copy(imageRect);
			emit PlayerCardChanged(playerIndex, cardIndex, cropped);
		}

		if ((cardIndex % 2) == 1)
		{	// Odd index
			// Add a card to the kitty
			Card *card = deck->GetNextCard();
			m_kitty->AddCardToHand(card);
			QImage image = card->getCardImage();
			QSize imageSize = image.size();
			QSize imageScaled = imageSize / 4;
			QImage cropped = image.scaled(imageScaled); // ) (copy(0, 0, 40, 40);
			// QRect imageRect(0, 0, 40, 40);
			//QPixmap croppedImage = image.copy(imageRect);
			emit PlayerCardChanged(static_cast<uint>(4), cardIndex/2, cropped);
		}
	}
}

