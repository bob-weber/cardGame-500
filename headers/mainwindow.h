#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QString>
#include <QLabel>

#include "card.h"
#include "clickableqlabel.h"
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
		void UpdateCard(QString labelName, Qt::MouseButtons buttons);

	private:
		Ui::MainWindow *ui;

		typedef struct {
			QString labelName;
			Card* card;
		} CardMappingT;

		// Maintain what card is displayed at each location on the table
		static CardMappingT playerCards[NUM_OF_HANDS][NUM_OF_CARDS_PER_PLAYER];

		/******************************************************************************************************************
		 * Given a string name, this function searches a mapping between this and the widget Id.
		 *
		 * Todo: What's a better way to determine which label generated a mouse event? How can I get rid of searching an
		 * array.
		 *
		 * Inputs
		 *	labelName:	the name of the label we're looking for.
		 *
		 * Outputs:
		 *	playerId:	If found, the id of the player the label is a part of. If not found, NUM_OF_HANDS.
		 *  cardId:   If found, the id of the card in the player's hand. If not found, NUM_OF_CARDS_PER_PLAYER.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void FindCardWidget(QString labelName, uint* playerId, uint* cardId);

};

#endif // MAINWINDOW_H
