#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QString>
#include <QLabel>

#include "card.h"
#include "game_settings.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT
		//QThread gameLogicThread;

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		// void SetPlayerCard(uint playerId, uint cardIndex, Card *card);

	public slots:
		void SetPlayerName(const uint player, const QString name);
		void SetPlayerAction(const uint player, const QString action);
		void SetTeamName(const uint teamId, const QString name);
		void SetTeamScore(const uint teamId, const int teamScore);
		void UpdateCardOnTable(uint player, uint cardIndex);
		void NewCard(uint playerId, uint cardIndex, Card *card);

	private:
		Ui::MainWindow *ui;

		// Maintain what card is displayed at each location on the table
		static Card* playerCards[NUM_OF_HANDS][NUM_OF_CARDS_PER_PLAYER];
};

#endif // MAINWINDOW_H
