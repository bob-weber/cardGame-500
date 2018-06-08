#include <type_traits>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamelogic_500.h"
#include "clickableqlabel.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	/* This threading logic follows the example given at
	 * https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
	 */
	QThread *gameLogicThread = new QThread;
	gameLogic_500 *gameLogic = new gameLogic_500();
	gameLogic->moveToThread(gameLogicThread);

	// Make Signal connections
	// Connect the "started" signal to the "PlayGame" slot. This is our main process in gameLogicThread.
	connect(gameLogicThread, SIGNAL (started()), gameLogic, SLOT (PlayGame()));

	/* Clean-up connections, for when the PlayGame process ends.
	 * gameLogic's "PlayGame" signals it's done by emitting "finished" signal. This will:
	 * 1. Call the game thread's "quit" function.
	 * 2. Call the game thread's "deleteLater" function, to schedule that object's deletion.
	 *
	 * The "finished" signal from the game thread will that thread's "deleteLater" function.
	 */
	connect(gameLogic, SIGNAL(finished()), gameLogicThread, SLOT(quit()));

	connect(gameLogic, SIGNAL (finished()), gameLogic, SLOT (deleteLater()));
	connect(gameLogicThread, SIGNAL (finished()), gameLogicThread, SLOT (deleteLater()));


	/* Connect signals from game thread that update the UI
	 */
	connect(gameLogic, SIGNAL(PlayerNameChanged(uint,QString)), this, SLOT(setPlayerName(uint,QString)));
	connect(gameLogic, SIGNAL(PlayerActionChanged(uint,QString)), this, SLOT(setPlayerAction(uint,QString)));
	connect(gameLogic, SIGNAL(PlayerCardChanged(uint, uint, QImage)), this, SLOT(setPlayerCardImage(uint,uint,QImage)));
	connect(ui->pb_Deal, SIGNAL(clicked()), gameLogic, SLOT(Deal()));

	// Connect label clicks to our handler
	connect(ui->lbl_P1C1, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C2, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C3, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C4, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C5, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C6, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C7, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C8, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C9, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P1C10, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));

	connect(ui->lbl_P2C1, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C2, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C3, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C4, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C5, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C6, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C7, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C8, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C9, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P2C10, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));

	connect(ui->lbl_P3C1, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C2, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C3, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C4, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C5, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C6, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C7, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C8, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C9, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P3C10, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));

	connect(ui->lbl_P4C1, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C2, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C3, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C4, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C5, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C6, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C7, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C8, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C9, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_P4C10, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));

	connect(ui->lbl_KittyC1, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_KittyC2, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_KittyC3, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_KittyC4, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));
	connect(ui->lbl_KittyC5, SIGNAL(clicked(uint,uint)), gameLogic, SLOT(CardClicked(uint,uint)));

	// Start the game thread, which will call PlayGame, due to the signal/slot connection.
	gameLogicThread->start();

}

MainWindow::~MainWindow()
{
	// Kill the game thread
	//gameLogicThread.quit();
	//gameLogicThread.wait();

	// Delete the UI
	delete ui;
}

void MainWindow::setPlayerName(const unsigned int player, const QString name)
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

void MainWindow::setPlayerAction(const unsigned int player, const QString &action)
{
	/*const*/ QLabel *lblActionPtrs[m_NumOfPlayers] =
	{
	  ui->lbl_P1Action, ui->lbl_P2Action, ui->lbl_P3Action, ui->lbl_P4Action, nullptr
	};

	if (player < m_NumOfPlayers)
	{
		/*const*/ QLabel *label = lblActionPtrs[player];
		if (label != nullptr)
		{
			label->setText(action);
		}
	}
	// else, ignore this request
}

void MainWindow::setPlayerCardImage(uint player, uint cardIndex, QImage image)
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
		label = lblCardPtrs[player][cardIndex];
		label->setPixmap(QPixmap::fromImage(image));
	}
	// else, ignore this request
}


