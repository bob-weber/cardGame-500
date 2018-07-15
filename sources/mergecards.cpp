#include <QObject>
#include "game_settings.h"

#include "mergecards.h"

MergeCards::MergeCards(QObject *parent)
{
}

void MergeCards::MergeHands(Player *player, Player *kitty)
{
	m_player = player;
	m_kitty = kitty;
	m_kittySelectedCardsCount = 0;
	m_playerSelectedCardsCount = 0;


	/* Pop up a dialog that explains how to merge the hand with the kitty.
	 * It contains an Ok and Reset button.
	 * Ok - the player is done merging the hand with the kitty. This is disabled unless the number of cards selected in
	 *      player's hand is the same as those selected in the kitty.
	 * Reset - Unselect all the cards and start over.
	 *
	 * When Ok is selected (and it's enabled), the selected cards in the kitty are exchanged with those selected in the
	 * player's hand.
	 */
	// Pop up a dialog to enable the user to exchange cards when the appropriate cards have been completed.
	m_mergeMsgBox = new QMessageBox;;
	QString msg = QString("%1, Select the cards in your hand, and in the kitty, that you want to exchange.\n\rThe number of cards selected must be the same.")
	                      .arg(m_player->GetPlayerName());
	QString informativeMsg = QString("When done, press \"Ok\". To reset and start over, hit \"Reset\".");
	m_mergeMsgBox->setText(msg);
	m_mergeMsgBox->setInformativeText(informativeMsg);
	m_mergeMsgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Reset);
	m_mergeMsgBox->setDefaultButton(QMessageBox::Ok);
	m_mergeMsgBox->setModal(false);
	m_mergeMsgBox->show();
}



#if 0
void MergeCards::CardSelectionChanged(uint playerId, bool cardIsRaised)
{
	if (playerId == KITTY_INDEX)
	{	// This is the kitty, not a player's hand
		if (cardIsRaised) {
			++m_kittySelectedCardsCount;
		}
		else {
			--m_kittySelectedCardsCount;
		}
	}
	else
	{	// This isn't the kitty
		/* For this game, the only 2 choices are a player's hand or a kitty.
		 * So, we don't need to verify that the playerId is the Id of the current bidder.
		 * The caller wouldn't call us without checking this. If it's not the kitty, it
		 * the winning bidder's hand.
		 */
		if (cardIsRaised) {
			++m_playerSelectedCardsCount;
		}
		else {
			--m_playerSelectedCardsCount;
		}
	}
}
#endif
