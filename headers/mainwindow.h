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
		void SetPlayerName(const uint player, const QString name);
		void SetPlayerAction(const uint player, const QString action);
		void SetTeamName(const uint teamId, const QString name);
		void SetTeamScore(const uint teamId, const int teamScore);
		void SetPlayerCardImage(uint player, uint cardIndex, QImage image, uint rotation, bool raised);

	private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
