#ifndef MERGEDIALOG_H
#define MERGEDIALOG_H

#include <QDialog>

namespace Ui {
	class MergeDialog;
}

class MergeDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit MergeDialog(uint numOfPlayerCardsSelected, uint numOfKittyCardsSelected, QWidget *parent = 0);
		~MergeDialog();

	public slots:
		void CheckSelectedNumOfCards(uint numOfPlayerCardsSelected, uint numOfKittyCardsSelected);

		void on_pb_Ok_clicked();

		void on_pb_StartOver_clicked();

	signals:
		void ClearSelectedCards();
		void CardSelectionComplete();

	private:
		Ui::MergeDialog *ui;
};

#endif // MERGEDIALOG_H
