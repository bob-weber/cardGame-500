#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QThread>
#include <QString>

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

	public slots:
		void SetPlayerName(const unsigned int player, const QString name);
		void SetPlayerAction(const unsigned int player, const QString &action);
		void SetPlayerCardImage(uint player, uint cardIndex, QImage image, uint rotation);

	private:
		Ui::MainWindow *ui;

		// Define some constants. Duplicates constants defined in the game. TODO: Fix this.
		const unsigned int m_NumOfPlayers = 5;		// 4 players + the kitty
		const unsigned int m_NumOfCards = 10;
};

#endif // MAINWINDOW_H