#ifndef USER_BID_DIALOG_H
#define USER_BID_DIALOG_H
#include <QDialog>
#include "bid.h"

/* This class manages a dialog window to get a user's bid. It verfies that the bid
 * is a valid bid for 500, but not that it exceeds the current bid. That's up to
 * the parent function, who can recall this dialog if the user wants to rebid.
 */

namespace Ui {
	class UserBidDialog;
}

class UserBidDialog : public QDialog
{
		Q_OBJECT

	public:
		/******************************************************************************************************************
		 * Constructor for the user's bidding dialog window
		 *
		 * A pointer to the parent object, "Bid", is passed in. This is so this dialog can
		 * utilize the helper functions available in Bid, such as determining if a bid is valid,
		 * getting the score, the text to display for a suit, etc. Signals/slots simply doesn't
		 * work well for this.
		 *
		 * Ideally, I'd make this class a subclass of Bid, but doing so in Qt
		 * is difficult because bot Bid and this class use QWidget as a parent, and this causes a
		 * compilation problem with which object to use. Subclassing in Qt seems difficult, at
		 * least to me at this time.
		 *
		 * Inputs
		 *	name:				Name of the current bidder. Used in dialogs.
		 *  parentBid:	Pointer to the parent class, to get access to bid functions.
		 *  parent:			Standard QWidget parent. Not used.
		 *
		 * Outputs:
		 *	m_bidderName:	Saved bidder name.
		 *  m_parentBid:	Saved pointer to the parent class
		 *
		 * Notes:
		 ******************************************************************************************************************/
		explicit UserBidDialog(QString *name, Bid *parentBid, QWidget *parent = 0);
		~UserBidDialog();

	signals:

	private slots:
		/******************************************************************************************************************
		 * Handlers for each user action on the Dialog screen. These are:
		 * 1. Clicking on a bid suit or a type of nellow.
		 * 2. Selecting the number of tricks.
		 * 3. Clicking on the "Bid" or "Pass" buttons.
		 *
		 * The "Bid" button is enabled/disabled based on when the bid is a valid 500 bid.
		 *
		 * If a type of nellow is selected, the # of tricks is set to 10, and all radioboxes for the
		 * number of tricks is disabled. All nellows are always 10 tricks.
		 *
		 * Inputs: None other than the event action.
		 *
		 * Outputs:
		 *  The bidding suit/nellow and number of tricks are updated in the parent Bid object.
		 *
		 * Notes:
		 ******************************************************************************************************************/
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

		// player info
		Bid *m_parentBid;
		QString *m_bidderName;

		/******************************************************************************************************************
		 * Enables/disables all of the "number of tricks" radio buttons.
		 * This is a convenience function for when a nellow bid is selected.
		 *
		 * Inputs:
		 *	enable:	If true, enables all these radioboxes. If false, disables them.
		 *
		 * Outputs:
		 *  None
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void controlNumOfTricksRadioButtons(bool enable);

		/******************************************************************************************************************
		 * Enables/disables the "Bid" pushbutton.
		 * Enables it if the bid is a valid 500 bid, either a nellow bid, or a bid suit and number of tricks have
		 * been specified. Othersise, it disables it.
		 *
		 * Inputs:
		 *	IsValid() check from the parent Bid object.
		 *
		 * Outputs:
		 *  None
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void controlBidPushButton();
};

#endif // USER_BID_DIALOG_H
