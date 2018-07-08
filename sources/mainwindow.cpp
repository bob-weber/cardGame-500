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
	connect(ui->actionDeal,    &QAction::triggered, gameLogic, &logic::Deal);
	connect(ui->actionBid,     &QAction::triggered, gameLogic, &logic::GetBids);
	connect(ui->actionQuit,    &QAction::triggered, qApp,      &QApplication::quit);

	// Connect game logic events to slots to update the GUI
	connect(gameLogic,       &logic::PlayerNameChanged,   this, &MainWindow::SetPlayerName);
	connect(gameLogic,       &logic::PlayerActionChanged, this, &MainWindow::SetPlayerAction);
	connect(gameLogic,       &logic::PlayerCardChanged,   this, &MainWindow::SetPlayerCardImage);

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
	gameLogic->PlayGame();

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

void MainWindow::SetPlayerName(const unsigned int player, const QString name)
{
	/*const*/ QLabel *lblNamePtrs[m_NumOfPlayers] =
	{
	  ui->lbl_P1Name, ui->lbl_P2Name, ui->lbl_P3Name, ui->lbl_P4Name, nullptr
	};

	if (player < m_NumOfPlayers)
	{
		/*const*/ QLabel *label = lblNamePtrs[player];
		if (label != nullptr)
		{
			label->setText(name);
		}
	}
	// else, ignore this request
}

void MainWindow::SetPlayerAction(const unsigned int player, const QString &action)
{
	/*const*/ QLabel *lblActionPtrs[m_NumOfPlayers] =
	{
	  ui->lbl_P1Action, ui->lbl_P2Action, ui->lbl_P3Action, ui->lbl_P4Action, nullptr
	};

	if (player < m_NumOfPlayers)
	{
		/*const*/ QLabel *label = lblActionPtrs[player];
		if (label != nullptr)
		{emit
			label->setText(action);
		}
	}
	// else, ignore this request
}

void MainWindow::SetPlayerCardImage(uint player, uint cardIndex, QImage image, uint rotation)
{
	QLabel *label = nullptr;

	/*const*/ QLabel *lblCardPtrs[m_NumOfPlayers][m_NumOfCards] =
	{
	  {	ui->lbl_P1C1, ui->lbl_P1C2, ui->lbl_P1C3, ui->lbl_P1C4, ui->lbl_P1C5, ui->lbl_P1C6, ui->lbl_P1C7, ui->lbl_P1C8, ui->lbl_P1C9, ui->lbl_P1C10 	},	// Player 1
	  {	ui->lbl_P2C1, ui->lbl_P2C2, ui->lbl_P2C3, ui->lbl_P2C4, ui->lbl_P2C5, ui->lbl_P2C6, ui->lbl_P2C7, ui->lbl_P2C8, ui->lbl_P2C9, ui->lbl_P2C10 	},	// Player 2
	  {	ui->lbl_P3C1, ui->lbl_P3C2, ui->lbl_P3C3, ui->lbl_P3C4, ui->lbl_P3C5, ui->lbl_P3C6, ui->lbl_P3C7, ui->lbl_P3C8, ui->lbl_P3C9, ui->lbl_P3C10 	},	// Player 3
	  {	ui->lbl_P4C1, ui->lbl_P4C2, ui->lbl_P4C3, ui->lbl_P4C4, ui->lbl_P4C5, ui->lbl_P4C6, ui->lbl_P4C7, ui->lbl_P4C8, ui->lbl_P4C9, ui->lbl_P4C10 	},	// Player 4
	  {	ui->lbl_KittyC1, ui->lbl_KittyC2, ui->lbl_KittyC3, ui->lbl_KittyC4, ui->lbl_KittyC5, nullptr, nullptr, nullptr, nullptr, nullptr }	// kitty
	};

	if ((player < m_NumOfPlayers) && (cardIndex < m_NumOfCards))
	{
		// Get the right label
		label = lblCardPtrs[player][cardIndex];

		// Rotate the image
		QMatrix matrix;
		matrix.rotate(rotation);
		QImage rotatedImage = image.transformed(matrix);

		// Update the image on the screen
		label->setPixmap(QPixmap::fromImage(rotatedImage));
	}
	// else, ignore this request
}

