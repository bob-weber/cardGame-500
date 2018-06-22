#include <QMessageBox>
#include "headers/gamelogic_500.h"

#include "headers/user_bid_dialog.h"
#include "ui_user_bid_dialog.h"

UserBidDialog::UserBidDialog(QString *name, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::UserBidDialog)
{
	ui->setupUi(this);

// (gameLogic_500::bid_suit, uint)

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
	m_name = name;
	QString introduction(*m_name);
	introduction.append(", what's your bid?");
	ui->lbl_Instruction->setText(introduction);

	//connect(this /*&dialog*/, &this->BidComplete, parent /*this*/, &gameLogic_500::SetBid);
	// connect(this /*&dialog*/, this->BBidComplete(gameLogic_500::bid_suit,uint)), parent /*this*/, SLOT(SetBid(gameLogic_500::bid_suit,uint)));

	// Default bid to no tricks, no suit
	m_numOfTricks = 0;
	m_suit = gameLogic_500::BID_NUM_OF_SUITS;
	controlBidPushButton();
}

UserBidDialog::~UserBidDialog()
{
	delete ui;
}

void UserBidDialog::on_rb_Spades_clicked()
{
	m_suit = gameLogic_500::BID_SPADES;

	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_Clubs_clicked()
{
	m_suit = gameLogic_500::BID_CLUBS;

	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_Diamonds_clicked()
{
	m_suit = gameLogic_500::BID_DIAMONDS;

	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_Hearts_clicked()
{
	m_suit = gameLogic_500::BID_HEARTS;

	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_NoTrump_clicked()
{
	m_suit = gameLogic_500::BID_NO_TRUMP;

	ui->gb_NumTricks->setEnabled(true);
	controlBidPushButton();
}

void UserBidDialog::on_rb_Nellow_clicked()
{
	m_numOfTricks = 10;
	m_suit = gameLogic_500::BID_NELLOW;

	ui->rb_10Tricks->setChecked(true);
	ui->gb_NumTricks->setEnabled(false);
	controlBidPushButton();
}

void UserBidDialog::on_rb_OpenNellow_clicked()
{
	m_numOfTricks = 10;
	m_suit = gameLogic_500::BID_OPEN_NELLOW;

	ui->rb_10Tricks->setChecked(true);
	ui->gb_NumTricks->setEnabled(false);
	controlBidPushButton();
}

void UserBidDialog::on_rb_DoubleNellow_clicked()
{
	m_numOfTricks = 10;
	m_suit = gameLogic_500::BID_DOUBLE_NELLOW;

	ui->rb_10Tricks->setChecked(true);
	ui->gb_NumTricks->setEnabled(false);
	controlBidPushButton();
}

void UserBidDialog::on_rb_6Tricks_clicked()
{
	m_numOfTricks = 6;
	controlBidPushButton();
}

void UserBidDialog::on_rb_7Tricks_clicked()
{
	m_numOfTricks = 7;
	controlBidPushButton();
}

void UserBidDialog::on_rb_8Tricks_clicked()
{
	m_numOfTricks = 8;
	controlBidPushButton();
}

void UserBidDialog::on_rb_9Tricks_clicked()
{
	m_numOfTricks = 9;
	controlBidPushButton();
}

void UserBidDialog::on_rb_10Tricks_clicked()
{
	m_numOfTricks = 10;
	controlBidPushButton();
}

void UserBidDialog::on_pb_Bid_clicked()
{
	emit BidComplete(m_suit, m_numOfTricks);

	QString suit;
	switch (m_suit)
	{
		case gameLogic_500::BID_SPADES:
			suit.append("spades");
			break;
		case gameLogic_500::BID_CLUBS:
			suit.append("clubs");
			break;
		case gameLogic_500::BID_DIAMONDS:
			suit.append("diamonds");
			break;
		case gameLogic_500::BID_HEARTS:
			suit.append("hearts");
			break;
		case gameLogic_500::BID_NO_TRUMP:
			suit.append("no trump");
			break;
		case gameLogic_500::BID_NELLOW:
			suit.append("nellow");
			break;
		case gameLogic_500::BID_OPEN_NELLOW:
			suit.append("open nellow");
			break;
		case gameLogic_500::BID_DOUBLE_NELLOW:
			suit.append("double nellow");
			break;
		default:
			// Should not get here
			throw("UserBidDialog::on_pb_Bid_clicked: invalid suit");
			break;
	}
	QString msg = QString("%1, you bid %2 %3.").arg(*m_name).arg(m_numOfTricks).arg(suit);

	QMessageBox msgBox;
	msgBox.setText(msg);
	msgBox.setInformativeText("Is this correct?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Yes)
	{
		// User has verified the bid. We're done.
		this->accept();
	}
	// else, user has cancelled the bid. Stay in this dialog
}

void UserBidDialog::on_pb_Pass_clicked()
{
	emit BidComplete(m_suit, m_numOfTricks);

	QString msg = QString("%1, you passed (no tricks).").arg(*m_name);
	QMessageBox msgBox;
	msgBox.setText(msg);
	msgBox.setInformativeText("Is this correct?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Yes)
	{
		// User has verified the bid. We're done.
		m_numOfTricks = 0;
		this->accept();
	}
	// else, user has cancelled the bid. Stay in this dialog
}


void UserBidDialog::controlBidPushButton()
{
	// See if we have a valid, non-zero bid
	bool validBid = ((m_numOfTricks > 0) && (m_suit != gameLogic_500::BID_NUM_OF_SUITS));
	ui->pb_Bid->setEnabled(validBid);
}

void UserBidDialog::controlNumOfTricksRadioButtons(bool enable)
{	// Enable/disable # of tricks selection
	ui->rb_6Tricks->setEnabled(enable);
	ui->rb_7Tricks->setEnabled(enable);
	ui->rb_8Tricks->setEnabled(enable);
	ui->rb_9Tricks->setEnabled(enable);
	ui->rb_10Tricks->setEnabled(enable);
}

void UserBidDialog::createVerificationMsg(QString *msg)
{
	if (m_numOfTricks > 0)
	{	// The player has made a bid
	}
	else
	{	// Passed
		*msg = QString("%1, you passed (no tricks).").arg(*m_name);
	}
}
