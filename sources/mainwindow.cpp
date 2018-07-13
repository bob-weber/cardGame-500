#include <type_traits>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic.h"

#include "clickableqlabel.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	/* This threading logic follows the example given at
	 * https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
	 */
	//QThread *gameLogicThread = new QThread;
	logic *gameLogic = new logic(/*this*/);
	//gameLogic->moveToThread(gameLogicThread);

	// Make Signal connections
	// Connect the "started" signal to the "PlayGame" slot. This is our main process in gameLogicThread.
	//connect(gameLogicThread, SIGNAL (started()), gameLogic, SLOT (PlayGame()));

	/* Clean-up connections, for when the PlayGame process ends.
	 * gameLogic's "PlayGame" signals it's done by emitting "finished" signal. This will:
	 * 1. Call the game thread's "quit" function.
	 * 2. Call the game thread's "deleteLater" function, to schedule that object's deletion.
	 *
	 * The "finished" signal from the game thread will that thread's "deleteLater" function.
	 */
	//connect(gameLogic, SIGNAL(finished()), gameLogicThread, SLOT(quit()));

	//connect(gameLogic, SIGNAL (finished()), gameLogic, SLOT (deleteLater()));
	//connect(gameLogicThread, SIGNAL (finished()), gameLogicThread, SLOT (deleteLater()));

	// Connect signals/slots for menu bar items
	connect(ui->actionNewGame, &QAction::triggered, gameLogic, &logic::NewGame);
	connect(ui->actionQuit,    &QAction::triggered, qApp,      &QApplication::quit);

	// Connect game logic events to slots to update the GUI
	connect(gameLogic, &logic::PlayerNameChanged,   this, &MainWindow::SetPlayerName);
	connect(gameLogic, &logic::PlayerActionChanged, this, &MainWindow::SetPlayerAction);
	connect(gameLogic, &logic::TeamNameChanged,     this, &MainWindow::SetTeamName);
	connect(gameLogic, &logic::TeamScoreChanged,    this, &MainWindow::SetTeamScore);
	connect(gameLogic, &logic::PlayerCardChanged,   this, &MainWindow::SetPlayerCardImage);


	// Connect GUI events to game logic slots
	connect(ui->lbl_P1C1,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C2,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C3,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C4,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C5,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C6,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C7,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C8,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C9,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P1C10,   &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);

	connect(ui->lbl_P2C1,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C2,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C3,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C4,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C5,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C6,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C7,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C8,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C9,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P2C10,   &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);

	connect(ui->lbl_P3C1,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C2,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C3,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C4,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C5,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C6,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C7,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C8,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C9,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P3C10,   &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);;

	connect(ui->lbl_P4C1,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C2,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C3,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C4,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C5,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C6,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C7,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C8,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C9,    &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_P4C10,   &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);

	connect(ui->lbl_KittyC1, &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_KittyC2, &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_KittyC3, &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_KittyC4, &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);
	connect(ui->lbl_KittyC5, &ClickableQLabel::clicked, gameLogic, &logic::CardClicked);

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
	static QLabel* const lblTeamScorePtrs[NUM_OF_TEAMS] =	{
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

void MainWindow::SetPlayerCardImage(uint player, uint cardIndex, QImage image, uint rotation, bool raised)
{
	static QLabel* const lblCardPtrs[NUM_OF_HANDS][NUM_OF_CARDS_PER_PLAYER] =
	{
	  {	ui->lbl_P1C1, ui->lbl_P1C2, ui->lbl_P1C3, ui->lbl_P1C4, ui->lbl_P1C5, ui->lbl_P1C6, ui->lbl_P1C7, ui->lbl_P1C8, ui->lbl_P1C9, ui->lbl_P1C10 	},	// Player 1
	  {	ui->lbl_P2C1, ui->lbl_P2C2, ui->lbl_P2C3, ui->lbl_P2C4, ui->lbl_P2C5, ui->lbl_P2C6, ui->lbl_P2C7, ui->lbl_P2C8, ui->lbl_P2C9, ui->lbl_P2C10 	},	// Player 2
	  {	ui->lbl_P3C1, ui->lbl_P3C2, ui->lbl_P3C3, ui->lbl_P3C4, ui->lbl_P3C5, ui->lbl_P3C6, ui->lbl_P3C7, ui->lbl_P3C8, ui->lbl_P3C9, ui->lbl_P3C10 	},	// Player 3
	  {	ui->lbl_P4C1, ui->lbl_P4C2, ui->lbl_P4C3, ui->lbl_P4C4, ui->lbl_P4C5, ui->lbl_P4C6, ui->lbl_P4C7, ui->lbl_P4C8, ui->lbl_P4C9, ui->lbl_P4C10 	},	// Player 4
	  {	ui->lbl_KittyC1, ui->lbl_KittyC2, ui->lbl_KittyC3, ui->lbl_KittyC4, ui->lbl_KittyC5, nullptr, nullptr, nullptr, nullptr, nullptr }	// kitty
	};

	if ((player < NUM_OF_HANDS) && (cardIndex < NUM_OF_CARDS_PER_PLAYER))
	{
		// Get the right label
		QLabel *label = nullptr;
		label = lblCardPtrs[player][cardIndex];
		if (label != nullptr)
		{
			// Rotate the image
			QMatrix matrix;
			matrix.rotate(rotation);
			QImage rotatedImage = image.transformed(matrix);

			// Update the image on the screen
			label->setPixmap(QPixmap::fromImage(rotatedImage));

			if (raised)
			{	// Raise the card
				label->setFrameStyle(QFrame::Panel | QFrame::Raised);
			}
			else
			{	// Lower it
				label->setFrameStyle(QFrame::Panel | QFrame::NoFrame);
			}
		}
		// else we don't have this label on the table top
	}
	// else, ignore this request
}

