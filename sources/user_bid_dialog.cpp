#include <QMessageBox>
#include "bid.h"

#include "user_bid_dialog.h"
#include "ui_user_bid_dialog.h"

UserBidDialog::UserBidDialog(uint bidderId, QString bidderName, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::UserBidDialog)
{
	ui->setupUi(this);
	this->m_bidderName = bidderName;

	// Create a local copy of this player's bid, setting the specified Id
	m_playerBid = new Bid();
	m_playerBid->Clear();
	m_playerBid->SetPlayerId(bidderId);

	// Set icons for suits
	QIcon *icon = new QIcon(":/resources/Suits/spade.svg");
	ui->rb_Spades->setIcon(*icon);

	icon->addFile(":/resources/Suits/club.svg");
	ui->rb_Clubs->setIcon(*icon);

	icon->addFile(":/resources/Suits/diamond.svg");
	ui->rb_Diamonds->setIcon(*icon);

	icon->addFile(":/resources/Suits/heart.svg");
	ui->rb_Hearts->setIcon(*icon);

	icon->addFile(":/resources/Suits/no_trump.svg");
	ui->rb_NoTrump->setIcon(*icon);

	// Update the introduction label
	QString introduction(m_bidderName);
	introduction.append(", what's your bid?");
	ui->lbl_Instruction->setText(introduction);

	controlBidPushButton();
}

UserBidDialog::~UserBidDialog()
{
	delete ui;
}

void UserBidDialog::on_rb_Spades_clicked()
{
	m_playerBid->SetBidSuit(Bid::BID_SPADES);
	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_Clubs_clicked()
{
	m_playerBid->SetBidSuit(Bid::BID_CLUBS);
	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_Diamonds_clicked()
{
	m_playerBid->SetBidSuit(Bid::BID_DIAMONDS);
	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_Hearts_clicked()
{
	m_playerBid->SetBidSuit(Bid::BID_HEARTS);
	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_NoTrump_clicked()
{
	m_playerBid->SetBidSuit(Bid::BID_NO_TRUMP);
	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_Nellow_clicked()
{
	m_playerBid->SetNumOfTricks(10);
	m_playerBid->SetBidSuit(Bid::BID_NELLOW);
	ui->rb_10Tricks->setChecked(true);
	ui->gb_NumTricks->setEnabled(false);
	controlBidPushButton();
}

void UserBidDialog::on_rb_OpenNellow_clicked()
{
	m_playerBid->SetNumOfTricks(10);
	m_playerBid->SetBidSuit(Bid::BID_OPEN_NELLOW);
	ui->rb_10Tricks->setChecked(true);
	ui->gb_NumTricks->setEnabled(false);
	controlBidPushButton();
}

void UserBidDialog::on_rb_DoubleNellow_clicked()
{
	m_playerBid->SetNumOfTricks(10);
	m_playerBid->SetBidSuit(Bid::BID_DOUBLE_NELLOW);
	ui->rb_10Tricks->setChecked(true);
	ui->gb_NumTricks->setEnabled(false);
	controlBidPushButton();
}

void UserBidDialog::on_rb_6Tricks_clicked()
{
	m_playerBid->SetNumOfTricks(6);
	controlBidPushButton();
}

void UserBidDialog::on_rb_7Tricks_clicked()
{
	m_playerBid->SetNumOfTricks(7);
	controlBidPushButton();
}

void UserBidDialog::on_rb_8Tricks_clicked()
{
	m_playerBid->SetNumOfTricks(8);
	controlBidPushButton();
}

void UserBidDialog::on_rb_9Tricks_clicked()
{
	m_playerBid->SetNumOfTricks(9);
	controlBidPushButton();
}

void UserBidDialog::on_rb_10Tricks_clicked()
{
	m_playerBid->SetNumOfTricks(10);
	controlBidPushButton();
}

void UserBidDialog::on_pb_Bid_clicked()
{
	QString msg = QString("%1, you bid %2.").arg(m_bidderName).arg(m_playerBid->GetBidText());
	QMessageBox msgBox;
	msgBox.setWindowTitle("Verify Your Bid");
	msgBox.setText(msg);
	msgBox.setInformativeText("Is this correct?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Yes)
	{
		/* Save the window position, so the next dialog pops up where this is.
		 * Do this before saving the bid, because the slot for that signal will launch
		 * the next bidding dialog, and we need to have saved the position first.
		 */
		QPoint position = this->pos();
		emit DialogPositionChanged(position);

		// User has verified the bid.
		emit PlayerHasBid(m_playerBid);

		// Close this dialog
		this->accept();
	}
	// else, user has cancelled the bid. Stay in this dialog
	// This path should never happen. The Bid pushbutton should be disabled.
}

void UserBidDialog::on_pb_Pass_clicked()
{
	QString msg = QString("%1, you passed (no tricks).").arg(m_bidderName);
	QMessageBox msgBox;
	msgBox.setWindowTitle("You're Passing?");
	msgBox.setText(msg);
	msgBox.setInformativeText("Is this correct?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Yes)
	{
		// Save the window position
		QPoint position = this->pos();
		emit DialogPositionChanged(position);

		// User has verified the bid. Clear the bid.
		m_playerBid->Clear();
		emit PlayerHasBid(m_playerBid);

		// Close this dialog
		this->accept();
	}
	// else, user has cancelled the bid. Stay in this dialog
}


void UserBidDialog::controlBidPushButton()
{
	// See if we have a valid, non-zero bid
	ui->pb_Bid->setEnabled(m_playerBid->IsValid());
}

void UserBidDialog::controlNumOfTricksRadioButtons(bool enable)
{	// Enable/disable # of tricks selection
	ui->rb_6Tricks->setEnabled(enable);
	ui->rb_7Tricks->setEnabled(enable);
	ui->rb_8Tricks->setEnabled(enable);
	ui->rb_9Tricks->setEnabled(enable);
	ui->rb_10Tricks->setEnabled(enable);
}

