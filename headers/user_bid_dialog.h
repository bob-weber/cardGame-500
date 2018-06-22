#ifndef USER_BID_DIALOG_H
#define USER_BID_DIALOG_H
#include <QDialog>

#include "headers/gamelogic_500.h"

namespace Ui {
	class UserBidDialog;
}

class UserBidDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit UserBidDialog(QString *name, QWidget *parent = 0);
		~UserBidDialog();

	signals:
		void BidComplete(gameLogic_500::bid_suit,uint);

	private slots:
		void on_rb_Spades_clicked();

		void on_rb_Clubs_clicked();

		void on_rb_Diamonds_clicked();

		void on_rb_Hearts_clicked();

		void on_rb_NoTrump_clicked();

		void on_rb_Nellow_clicked();

		void on_rb_OpenNellow_clicked();

		void on_rb_DoubleNellow_clicked();

		void on_rb_6Tricks_clicked();

		void on_rb_7Tricks_clicked();

		void on_rb_8Tricks_clicked();

		void on_rb_9Tricks_clicked();

		void on_rb_10Tricks_clicked();

		void on_pb_Bid_clicked();

		void on_pb_Pass_clicked();

	private:
		Ui::UserBidDialog *ui;

		// Bid values
		uint m_numOfTricks;
		gameLogic_500::bid_suit m_suit;
		QString *m_name;

		void controlNumOfTricksRadioButtons(bool enable);
		void controlBidPushButton();
		void createVerificationMsg(QString *msg);
};

#endif // USER_BID_DIALOG_H
