#ifndef SELECTCARDDIALOG_H
#define SELECTCARDDIALOG_H

#include <QDialog>
#include "player.h"
#include "bid.h"
#include "card.h"

namespace Ui {
	class selectCardDialog;
}

class selectCardDialog : public QDialog
{
		Q_OBJECT

	public:
		/******************************************************************************************************************
		 * This constructor copies the passed parameters to this class, so we can use them while this dialog is active.
		 * Launches the dialog.
		 * Destructor cleans up the UI when the dialog closes.
		 *
		 * Inputs:
		 *	 Player:		Player that's selecting the card.
		 *   trumpSuit:	The trump suit, if any.
		 *	 leadCard:	Led card, if any.
		 *
		 * Outputs:
		 *	 m_player, m_trumpSuit, m_leadCard:	Saved parameters for using during card selection.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		explicit selectCardDialog(Player* player, Bid::bidSuitT trumpSuit, Card* leadCard, QWidget *parent = nullptr);
		~selectCardDialog();

	public slots:
		/******************************************************************************************************************
		 * This slot is called when a card has been selected/unselected on the GUI.
		 * The card play is validated. If it's not valid, it's deselected.
		 * The "Ok" button is enabled if only 1 valid card is selected. Otherwise it's disabled.
		 *
		 * Inputs:
		 *	 playerId:	The Id of the player who had a card selected.
		 *   cardId:		The selected/unselected card
		 *
		 * Outputs:
		 *	 m_cardId:	Updated to the selected card if it's valid.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void CardSelected(uint playerId, uint cardId);

		/******************************************************************************************************************
		 * When the user is done selected a card to play, clicking this button will termiante this dialog and notify the
		 * callering class that card selection is complete.
		 * The "Ok" button is only enabled if only 1 valid card is selected.
		 *
		 * Inputs:
		 *	 None. Called when the user pressed Ok on the dialog.
		 *
		 * Outputs:
		 *	 None
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void on_buttonBox_accepted();

	signals:
		/******************************************************************************************************************
		 * This signal is emitted if this function changes a card's selection, because it's not a valid card to play.
		 * This notifies the GUI to udpate the card's selection status.
		 *
		 * Outputs:
		 *	 m_cardId:	The Id of the selected card
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void CardSelectionComplete(uint m_cardId);

	private:
		/******************************************************************************************************************
		 * Determines of this card is a valid play. This depends on what card was led for this round, if any, and what the
		 * is the trump suit.
		 *
		 * Inputs:
		 *	 cardToCheck:	Card to check
		 *   m_leadCard:	Lead card
		 *	 m_trumpSuit:	The trump suit
		 *
		 * Outputs:
		 *	 Returns true if this card is a valid play. False if not.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		bool CheckForValidPlay(Card* cardToCheck);

		Ui::selectCardDialog *ui;		// Dialog UI

		Player* m_player;						// Player to select a card
		Bid::bidSuitT m_trumpSuit;	// Bid for this hand
		Card* m_leadCard;						// Lead card for a round
		uint m_cardId;							// Card Id of the selected card
};

#endif // SELECTCARDDIALOG_H
