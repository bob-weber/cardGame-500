#include <type_traits>
#include <QLabel>
#include <QSignalMapper>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickableqlabel.h"
#include "logic.h"
#include "card.h"

#include "clickableqlabel.h"

// Card* MainWindow::playerCards[NUM_OF_HANDS][NUM_OF_CARDS_PER_PLAYER];

//using namespace Ui_MainWindow;
MainWindow::CardMappingT MainWindow::playerCards[NUM_OF_HANDS][NUM_OF_CARDS_PER_PLAYER] =
{
  {	// Player 1
    { "lbl_P1C1",  nullptr },
    { "lbl_P1C2",  nullptr },
    { "lbl_P1C3",  nullptr },
    { "lbl_P1C4",  nullptr },
    { "lbl_P1C5",  nullptr },
    { "lbl_P1C6",  nullptr },
    { "lbl_P1C7",  nullptr },
    { "lbl_P1C8",  nullptr },
    { "lbl_P1C9",  nullptr },
    { "lbl_P1C10", nullptr },
  },

  {	// Player 2
    { "lbl_P2C1",  nullptr },
    { "lbl_P2C2",  nullptr },
    { "lbl_P2C3",  nullptr },
    { "lbl_P2C4",  nullptr },
    { "lbl_P2C5",  nullptr },
    { "lbl_P2C6",  nullptr },
    { "lbl_P2C7",  nullptr },
    { "lbl_P2C8",  nullptr },
    { "lbl_P2C9",  nullptr },
    { "lbl_P2C10", nullptr },
  },

  {	// Player 3
    { "lbl_P3C1",  nullptr },
    { "lbl_P3C2",  nullptr },
    { "lbl_P3C3",  nullptr },
    { "lbl_P3C4",  nullptr },
    { "lbl_P3C5",  nullptr },
    { "lbl_P3C6",  nullptr },
    { "lbl_P3C7",  nullptr },
    { "lbl_P3C8",  nullptr },
    { "lbl_P3C9",  nullptr },
    { "lbl_P3C10", nullptr },
  },

  {	// Player 4
    { "lbl_P4C1",  nullptr },
    { "lbl_P4C2",  nullptr },
    { "lbl_P4C3",  nullptr },
    { "lbl_P4C4",  nullptr },
    { "lbl_P4C5",  nullptr },
    { "lbl_P4C6",  nullptr },
    { "lbl_P4C7",  nullptr },
    { "lbl_P4C8",  nullptr },
    { "lbl_P4C9",  nullptr },
    { "lbl_P4C10", nullptr },
  },

  {	// Player 4
    { "lbl_KittyC1",  nullptr },
    { "lbl_KittyC2",  nullptr },
    { "lbl_KittyC3",  nullptr },
    { "lbl_KittyC4",  nullptr },
    { "lbl_KittyC5",  nullptr },
    { "",             nullptr },
    { "",             nullptr },
    { "",             nullptr },
    { "",             nullptr },
    { "",             nullptr },
  },
};

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	logic *gameLogic = new logic(/*this*/);

	// Connect signals/slots for menu bar items
	connect(ui->actionNewGame, &QAction::triggered, gameLogic, &logic::NewGame);
	connect(ui->actionQuit,    &QAction::triggered, qApp,      &QApplication::quit);

	// Connect game logic events to slots to update the GUI
	connect(gameLogic, &logic::PlayerNameChanged,   this, &MainWindow::SetPlayerName);
	connect(gameLogic, &logic::PlayerActionChanged, this, &MainWindow::SetPlayerAction);
	connect(gameLogic, &logic::TeamNameChanged,     this, &MainWindow::SetTeamName);
	connect(gameLogic, &logic::TeamScoreChanged,    this, &MainWindow::SetTeamScore);
	connect(gameLogic, &logic::SetPlayerCard,				this, &MainWindow::NewCard);
	connect(gameLogic, &logic::CardChanged,					this, &MainWindow::UpdateCardOnTable);

	// Connect GUI events to game logic slots
	connect(ui->lbl_P1C1,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C2,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C3,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C4,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C5,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C6,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C7,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C8,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C9,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P1C10,   &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);

	connect(ui->lbl_P2C1,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C2,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C3,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C4,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C5,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C6,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C7,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C8,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C9,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P2C10,   &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);

	connect(ui->lbl_P3C1,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C2,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C3,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C4,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C5,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C6,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C7,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C8,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C9,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P3C10,   &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);;

	connect(ui->lbl_P4C1,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C2,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C3,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C4,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C5,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C6,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C7,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C8,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C9,    &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_P4C10,   &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);

	connect(ui->lbl_KittyC1, &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_KittyC2, &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_KittyC3, &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_KittyC4, &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);
	connect(ui->lbl_KittyC5, &ClickableQLabel::cardClicked, this, &MainWindow::UpdateCard);

	// Setup the playing table, and start the game
	gameLogic->SetupTable();
	// gameLogic->NewGame();

	// Start the game thread, which will call PlayGame, due to the signal/slot connection.
	//gameLogicThread->start();

}

MainWindow::~MainWindow()
{
	// Kill the game thread
	//gameLogicThread.quit();
	//gameLogicThread.wait();

	// Delete the UI
	delete ui;
}

void MainWindow::SetPlayerName(const uint playerId, const QString name)
{
	static QLabel* const lblNamePtrs[NUM_OF_PLAYERS] = {
	  ui->lbl_P1Name, ui->lbl_P2Name, ui->lbl_P3Name, ui->lbl_P4Name
	};

	if (playerId < NUM_OF_PLAYERS)
	{
		QLabel *label = nullptr;
		label = lblNamePtrs[playerId];
		if (label != nullptr) {
			label->setText(name);
		}
	}
	// else, ignore this request
}

void MainWindow::SetPlayerAction(const uint playerId, const QString action)
{
	static QLabel* const lblActionPtrs[NUM_OF_PLAYERS] = {
	  ui->lbl_P1Action, ui->lbl_P2Action, ui->lbl_P3Action, ui->lbl_P4Action
	};

	if (playerId < NUM_OF_PLAYERS)
	{
		QLabel *label = nullptr;
		label = lblActionPtrs[playerId];
		if (label != nullptr) {
			label->setText(action);
		}
	}
	// else, ignore this request
}

void MainWindow::SetTeamName(const uint teamId, const QString name)
{
	static QLabel* const lblTeamNamePtrs[NUM_OF_TEAMS] =	{
	  ui->lbl_NameTeam1, ui->lbl_NameTeam2
	};

	if (teamId < NUM_OF_TEAMS)
	{
		QLabel *label = nullptr;
		label = lblTeamNamePtrs[teamId];
		if (label != nullptr) {
			label->setText(name);
		}
		// else, invalid ptr. This should never happen; it'd be a logic error.
	}
	// else, ignore this invalid request
}

void MainWindow::SetTeamScore(const uint teamId, const int teamScore)
{
	QLabel* const lblTeamScorePtrs[NUM_OF_TEAMS] =	{
	  ui->lbl_Score1, ui->lbl_Score2
	};

	if (teamId < NUM_OF_TEAMS)
	{
		QLabel *label = nullptr;
		label = lblTeamScorePtrs[teamId];
		if (label != nullptr) {
			QString score = QString("%1").arg(teamScore);
			label->setText(score);
		}
		// else, invalid ptr. This should never happen; it'd be a logic error.
	}
	// else, ignore this invalid request
}

void MainWindow::NewCard(uint playerId, uint cardIndex, Card *card)
{
	// Update the card
	// Checking the bounds shouldn't be necessary, but we'll be paranoid.
	if ((playerId < NUM_OF_HANDS) && (cardIndex < NUM_OF_CARDS_PER_PLAYER))
	{
		playerCards[playerId][cardIndex].card = card;
	}

	// Update the card image
	UpdateCardOnTable(playerId, cardIndex);
}

void MainWindow::UpdateCardOnTable(uint player, uint cardIndex)
{
	static QLabel* lblCardPtrs[NUM_OF_HANDS][NUM_OF_CARDS_PER_PLAYER] =
	{
	  {	ui->lbl_P1C1, ui->lbl_P1C2, ui->lbl_P1C3, ui->lbl_P1C4, ui->lbl_P1C5, ui->lbl_P1C6, ui->lbl_P1C7, ui->lbl_P1C8, ui->lbl_P1C9, ui->lbl_P1C10 	},	// Player 1
	  {	ui->lbl_P2C1, ui->lbl_P2C2, ui->lbl_P2C3, ui->lbl_P2C4, ui->lbl_P2C5, ui->lbl_P2C6, ui->lbl_P2C7, ui->lbl_P2C8, ui->lbl_P2C9, ui->lbl_P2C10 	},	// Player 2
	  {	ui->lbl_P3C1, ui->lbl_P3C2, ui->lbl_P3C3, ui->lbl_P3C4, ui->lbl_P3C5, ui->lbl_P3C6, ui->lbl_P3C7, ui->lbl_P3C8, ui->lbl_P3C9, ui->lbl_P3C10 	},	// Player 3
	  {	ui->lbl_P4C1, ui->lbl_P4C2, ui->lbl_P4C3, ui->lbl_P4C4, ui->lbl_P4C5, ui->lbl_P4C6, ui->lbl_P4C7, ui->lbl_P4C8, ui->lbl_P4C9, ui->lbl_P4C10 	},	// Player 4
	  {	ui->lbl_KittyC1, ui->lbl_KittyC2, ui->lbl_KittyC3, ui->lbl_KittyC4, ui->lbl_KittyC5, nullptr, nullptr, nullptr, nullptr, nullptr }	// kitty
	};
	if ((player < NUM_OF_HANDS) && (cardIndex < NUM_OF_CARDS_PER_PLAYER))
	{
		// Get the card we want to update, and it's location on the table
		QLabel *label = lblCardPtrs[player][cardIndex];
		Card *card = playerCards[player][cardIndex].card;

		if ((label != nullptr) && (card != nullptr))
		{	// We have a valid card, and a valid location to update
			// Rotate the image
			QMatrix matrix;
			matrix.rotate(card->GetRotation());
			QImage rotatedImage;
			if (card->GetOrientation() == Card::FACE_DOWN) {
				rotatedImage = card->GetBackImage();
			}
			else {
				rotatedImage = card->GetFaceImage();
			}
			rotatedImage = rotatedImage.transformed(matrix);

			// Update the image on the screen
			label->setPixmap(QPixmap::fromImage(rotatedImage));

			if (card->IsSelected())
			{	// Raise the card
				label->setLineWidth(3);
				label->setFrameStyle(QFrame::Box /*| QFrame::NoFrame*/ | QFrame::Raised);
			}
			else
			{	// Lower it
				label->setLineWidth(0);
				label->setFrameStyle(QFrame::Panel);
			}
		}
		// else we don't have this label on the table top
	}
	// else, ignore this request
}

void MainWindow::UpdateCard(QString labelName, Qt::MouseButtons buttons)
{
	/* Handle clicking on cards. There are 2 possible actions;
	 * 1. Left click. This selects and de-selecs a card.
	 * 2. Right click. This flips the card over.
	 */

	// Find the lable that generated the mouse event.
	uint playerId, cardId;
	FindCardWidget(labelName, &playerId, &cardId);
	if ((playerId < NUM_OF_HANDS) && (cardId < NUM_OF_CARDS_PER_PLAYER))
	{	// We found the clicked card
		Card* playerCard = playerCards[playerId][cardId].card;

		if ((buttons & Qt::LeftButton) != 0)
		{	// The left button was clicked
			// Raise/lower the card
			bool cardIsSelected = playerCard->IsSelected();
			playerCard->SetSelected(!cardIsSelected);
		}
		else if ((buttons & Qt::RightButton) != 0)
		{	// Right button clicked
			// Flip the card
			// Flip it, like normal.
			playerCard->FlipOrientation();
		}
		// else, some other button event that we ignore.

		UpdateCardOnTable(playerId, cardId);
	}
	// else, we didn't find the specified card
}

void MainWindow::FindCardWidget(QString labelName, uint* playerId, uint* cardId)
{
	// Initialize return values to invalid values
	*playerId =  NUM_OF_HANDS;
	*cardId   =  NUM_OF_CARDS_PER_PLAYER;

	for (uint playerIndex = 0; playerIndex < NUM_OF_HANDS; playerIndex++)
	{
		for (uint cardIndex = 0; cardIndex < NUM_OF_CARDS_PER_PLAYER; cardIndex++)
		{
			if (playerCards[playerIndex][cardIndex].labelName == labelName)
			{	// We found the specified card
				*playerId = playerIndex;
				*cardId = cardIndex;
				break;	// done searching
			}
			// else, this isn't the specified card
		}	// for each card
	}	// for each player
}
