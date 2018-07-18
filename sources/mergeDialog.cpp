#include <QString>

#include "mergeDialog.h"
#include "ui_mergeDialog.h"

MergeDialog::MergeDialog(uint numOfPlayerCardsSelected, uint numOfKittyCardsSelected, QWidget *parent):
  QDialog(parent),
  ui(new Ui::MergeDialog)
{
	ui->setupUi(this);

	QString numOfCardsSelected = QString("%1").arg(numOfPlayerCardsSelected);
	ui->lbl_NumPlayer->setText(numOfCardsSelected);
	numOfCardsSelected = QString("%1").arg(numOfKittyCardsSelected);
	ui->lbl_NumKitty->setText(numOfCardsSelected);
}

MergeDialog::~MergeDialog()
{
	delete ui;
}

void MergeDialog::CheckSelectedNumOfCards(uint numOfPlayerCardsSelected, uint numOfKittyCardsSelected)
{
	QString numOfCardsSelected = QString("%1").arg(numOfPlayerCardsSelected);
	ui->lbl_NumPlayer->setText(numOfCardsSelected);
	numOfCardsSelected = QString("%1").arg(numOfKittyCardsSelected);
	ui->lbl_NumKitty->setText(numOfCardsSelected);

	if (numOfPlayerCardsSelected == numOfKittyCardsSelected)
	{	// Okay to merge cards. Enable Ok button.
		ui->pb_Ok->setEnabled(true);
	}
	else
	{
		ui->pb_Ok->setEnabled(false);
	}
}

void MergeDialog::on_pb_Ok_clicked()
{
	emit CardSelectionComplete();

	// Close this dialog
	this->accept();
}

void MergeDialog::on_pb_StartOver_clicked()
{
	emit ClearSelectedCards();
}
