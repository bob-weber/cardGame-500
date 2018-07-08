#include "headers/deck.h"
#include "headers/player.h"
#include "headers/user_bid_dialog.h"

#include "gamelogic_500.h"

using namespace std;

// Define constants here, so we can use them in structure definitions
const uint m_numOfTeams = 2;
const uint m_numOfPlayers = 4;
const uint m_numOfHands = m_numOfPlayers + 1;
const uint m_KittyIndex = 4;
const uint m_numOfCardsPerPlayer = 10;
const uint m_numOfCardsInKitty = 5;

const uint BidValue[gameLogic_500::BID_NUM_OF_SUITS][m_numOfCardsPerPlayer] =
{	//   1    2    3    4    5    6    7    8    9    10
  // ----  ---  ---  ---  ---  ---  ---  ---  ---  ---
  {     0,   0,   0,   0,   0,  40, 140, 240, 340, 440 },	// Spades bid
  {     0,   0,   0,   0,   0,  60, 160, 260, 360, 460 },	// Clubs bid
  {     0,   0,   0,   0,   0,  80, 180, 280, 380, 480 },	// Diamonds bid
  {     0,   0,   0,   0,   0, 100, 200, 300, 400, 500 },	// Hearts bid
  {     0,   0,   0,   0,   0, 120, 220, 320, 420, 520 },	// No Trump bid
  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 250 },	// Nellow bid
  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 500 },	// Open nellow bid
  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 500 },	// Double nellow bid
};

typedef struct {
	QString name;
	uint GUI_ID;
	uint maxNumOfCards;
	uint currentNumOfCards;
	uint cardRotation;
	uint teamID;	// 0=no team. >0 with the same id groups players on a team.
} playerT;
playerT m_PlayerInfo[m_numOfHands] =
{
  // ID 0-3 are the regular players
  // ID 4 is the kitty
  // ID        GUI ID  Max # Cards  Current # Cards  Card Rotation  Team ID  Bid Trump  Bid Num of Tricks
  { "Kathy",     0,             m_numOfCardsPerPlayer, 0,   0, 1 },
  { "Theodore",  1,             m_numOfCardsPerPlayer, 0,  90, 2 },
  { "Priya",     2,             m_numOfCardsPerPlayer, 0, 180, 1 },
  { "Edward",    3,             m_numOfCardsPerPlayer, 0, 270, 2 },
  { "",          4,  m_numOfCardsInKitty,   0,   0, 0 }
};


gameLogic_500::gameLogic_500(QWidget *parent) : QWidget(parent)
{
	/* Allocate player instances in the constructor
	 * Since we delete them in the destructor, it's more logical to allocate them here, rather than rely on
	 * another function being called after the constructor.
	 */
	m_player = new Player *[m_numOfHands];
	for (uint playerIndex = 0; playerIndex < m_numOfHands; playerIndex++)
	{
		m_player[playerIndex] = new Player();

	}

	/* Do not do other initialization here that relies on signals and slots.
	 * The parent sets up these connections. We;ll do this in SetupTable(), which the parent will call.
	 */
}

void gameLogic_500::SetupTable()
{
	/********************************************************************************************************************
	 * Setup the deck, players, etc.
	 ********************************************************************************************************************/
	// Create a deck
	deck = new Deck(Deck::DECK_4S_AND_UP, 1, 1);
	deck->Print();

	// Initialize the playersDealCards
	for (uint playerIndex = 0; playerIndex < m_numOfHands; playerIndex++)
	{
		// Set each player's ID
		m_player[playerIndex]->SetID(m_PlayerInfo[playerIndex].GUI_ID);

		// All players start of with no cards
		m_player[playerIndex]->SetCurrentNumOfCards(0);

		// Max # of cards depends on whether this is a normal player or the kitty
		m_player[playerIndex]->SetMaxNumOfCards(m_PlayerInfo[playerIndex].maxNumOfCards);

		if (playerIndex < m_KittyIndex)
		{	// Not the kitty
			// Update the player's GUI name
			emit PlayerNameChanged(m_PlayerInfo[playerIndex].GUI_ID, m_PlayerInfo[playerIndex].name);
			emit PlayerActionChanged(m_PlayerInfo[playerIndex].GUI_ID, "Wait");
		}

		// Set the card's rotation on the GUI
		m_player[playerIndex]->SetCardRotation(m_PlayerInfo[playerIndex].cardRotation);
	}
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
	/********************************************************************************************************************
	 * Start a new game
	 * This returns when the game is complete.
	 ********************************************************************************************************************/
	NewGame();

	// TODO: pop-up to display winner
}

void gameLogic_500::NewGame()
{
	// The deal starts with player 0
	m_dealer = 0;
	Deal();

	//Bid();
	//PlayHand();
	//Score();
}

void gameLogic_500::SetBid(bid_suit suit, uint numOfTricks)
{
	this->m_bidStatus.suit = suit;
	this->m_bidStatus.numOfTricks = numOfTricks;
}

void gameLogic_500::SetBidPlayerID(uint ID)
{
	this->m_bidStatus.playerID = ID;
}

gameLogic_500::bidT *gameLogic_500::GetBid()
{
	return &(this->m_bidStatus);
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
	DealCards();
}

void gameLogic_500::DealCards()
{
	// Deal all cards
	// 10 go to each player, and 5 to the kitty.
	uint playerIndex = m_dealer;
	bool dealToKittyThisPass = false;
	uint cardIndex = 0;
	while (cardIndex < deck->GetTotalCardCount())
	{
		AddCardToPlayer(m_player[playerIndex], deck->GetNextCard());
		++cardIndex;

		// Advance to the next player
		// We include the kitty in this sequence, but if it's not time to deal to the kitty, we'll skip it.
		playerIndex = advanceIndex(playerIndex, m_numOfHands);
		if (playerIndex == m_KittyIndex)
		{	// Next index is to deal to the kitty
			if (dealToKittyThisPass)
			{	// Do nothing with the index. We're going to do that on the next pass.
				// Clear the flag for the next pass.
				dealToKittyThisPass = false;
			}
			else
			{	// We're not going to deal to the kitty
				// Advance the pointer again, past the kitty
				playerIndex = advanceIndex(playerIndex, m_numOfHands);
				// Set the flag for the next pass.
				dealToKittyThisPass = true;
			}
		}
		// else, not the kitty
		// Nothing special to do
	}	// while
}

/******************************************************************************************************************
 * Starting with the player to the left of the dealer, get bids.
 * Verify each successive bid is > than the current bid. When the dealer has bid, bidding is complete.
 * Return to the calling function.
 *
 *
 * Inputs:
 *	None passed, but m_bidStatus is updated as we go through each player.
 *
 * Outputs:
 *	m_bidStatus: Keeps track of the current and winning bid.
 *
 * Notes:
 *	If no player bids, it's up to the claling function to check for this, and reshuffle the cards.
 ******************************************************************************************************************/
void gameLogic_500::Bid()
{
	// Get the bid for each player, starting to the left of the dealer
	m_activePlayer = m_dealer + 1;
	for (uint i=0; i < (m_numOfHands-1); i++)
	{
		QString playerName(m_PlayerInfo[m_activePlayer].name);
		//playerInstruction->((m_PlayerInfo[playerIndex].name);
		UserBidDialog dialog(&playerName, this);
		//userBidForm.setWindowModality(Qt::Modaless);
		// bidUI.setModal(true);	// Block until the user enters a bid

		/* Connect signals/slots
		 * I had trouble getting the connection to work from within the dialog.
		 * It works making the connection here. Do this by default.
		 *
		 * old format: connect(&dialog, SIGNAL(BidComplete(gameLogic_500::bid_suit,uint)), this, SLOT(SetBid(gameLogic_500::bid_suit,uint)));
		 */
		connect(&dialog, &UserBidDialog::BidComplete, this, &gameLogic_500::SetBid);

		auto test = dialog.exec();
		if (test == QDialog::Accepted)
		{
			m_activePlayer = advanceIndex(m_activePlayer, (m_numOfHands-1));
		}
		else
		{	/* The user aborted the bid box
			 * What does that mean, they want to abort the game?
			 * Let's assume that's true. Otherwise, if they did want to, we'd be stuck in the bidding modal dialog,
			 * and they couldn't get to the main window to close it.
			 */
			exit(EXIT_SUCCESS);
		}
	}

}

void gameLogic_500::CardClicked(uint player, uint card)
{
	Card *playerCard = nullptr;
	uint cardRotation = 0;
	// Find the player that matches our player index
	for (uint playerIndex = 0; playerIndex < m_numOfHands; playerIndex++)
	{
		if (m_player[playerIndex]->GetID() == player)
		{	// This is the player who's card was clicked
			playerCard = m_player[playerIndex]->GetCard(card);
			cardRotation = m_player[playerIndex]->GetCardRotation();
			break;
		}
		// else, not the correct player
	}	// for

	if (playerCard != nullptr)
	{	// We have a valid card
		Card::Orientation orientation = playerCard->FlipOrientation();
		if (orientation == Card::FACE_DOWN) {
			emit PlayerCardChanged(player, card, playerCard->GetBackImage(), cardRotation);
		}
		else {
			emit PlayerCardChanged(player, card, playerCard->GetFaceImage(), cardRotation);
		}
	}
	// else, this card hasn't been dealt yet or we didn't find it
}

void gameLogic_500::AddCardToPlayer(Player *player, Card *card)
{
	//cout << "player=" << playerIndex << ", card=" << cardIndex << endl;

	// Get the next card in the deck and add it to this player's hand.
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
		uint cardRotation = player->GetCardRotation();
		emit PlayerCardChanged(player->GetID(), handIndex, image, cardRotation);
	}
	else
	{
		throw out_of_range("gameLogic_500::AddCardToPlayer: Couldn't add card to player.");
	}
}

uint gameLogic_500:: advanceIndex(uint index, const uint max)
{
	++index;
	if (index >= max) {
		index = 0;
	}
	return index;
}
