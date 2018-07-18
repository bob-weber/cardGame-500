#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QString>
#include <QLabel>

#include "deck.h"
#include "card.h"
#include "clickableqlabel.h"
#include "game_500_settings.h"
#include "player.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		// void SetPlayerCard(uint playerId, uint cardIndex, Card *card);

	public slots:
		void SetPlayerName(const uint player, const QString name);
		void SetPlayerAction(const uint player, const QString action);
		void SetTeamName(const uint teamId, const QString name);
		void SetTeamScore(const uint teamId, const int teamScore);
		void UpdateClickedCard(QString labelName, Qt::MouseButtons buttons);
		void UpdateCard(uint player, uint cardId);

	signals:
		void CardSelectionChanged(uint playerId, uint cardId);
		void CardOrientationChanged(uint playerId, uint cardId);

	private:
		Ui::MainWindow *ui;

		typedef struct {
			QString labelName;
			Card* card;
		} CardMappingT;

		// Maintain what card is displayed at each location on the table
		static CardMappingT cardLabelMapping[NUM_OF_HANDS][NUM_OF_CARDS_PER_PLAYER];

		// Deck and players used in this game
		Deck *m_deck;					// The deck we're playing with
		Player **m_player;	// Array of players

		// Define information for each player.
		// TODO: Move game-specific info like this to a game-specific file.
		typedef struct {
			QString name;
			uint cardRotation;
			uint teamID;	// 0=no team. >0 with the same id groups players on a team.
			uint maxNumOfCards;
		} playerT;
		playerT m_PlayerInfo[NUM_OF_HANDS] =
		{
		  // ID 0-3 are the regular players
		  // ID 4 is the kitty
		  // ID         Card Rotation  Team ID	Num of Cards
		  // ---------  -------------  -------	------------
		  { "Kathy",               0,       1,  NUM_OF_CARDS_PER_PLAYER },
		  { "Theodore",           90,       2,  NUM_OF_CARDS_PER_PLAYER },
		  { "Priya",             180,       1,  NUM_OF_CARDS_PER_PLAYER	},
		  { "Edward",            270,       2,  NUM_OF_CARDS_PER_PLAYER	},
		  { "Kitty",               0,       0,  NUM_OF_CARDS_IN_KITTY		}
		};

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
