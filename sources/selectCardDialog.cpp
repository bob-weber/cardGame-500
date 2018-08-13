#include "player.h"
#include "bid.h"
#include "card.h"
#include "mainwindow.h"

#include "selectCardDialog.h"
#include "ui_selectCardDialog.h"

selectCardDialog::selectCardDialog(Player* player, Bid::bidSuitT trumpSuit, Card* leadCard, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::selectCardDialog)
{
	m_player = player;
	m_trumpSuit = trumpSuit;
	m_leadCard = leadCard;

	ui->setupUi(this);
	ui->lbl_name->setText(m_player->GetPlayerName());
	ui->buttonBox->setEnabled(false);
}

selectCardDialog::~selectCardDialog()
{
	delete ui;
}

void selectCardDialog::CardSelected(uint playerId, uint cardId)
{
	if (playerId == m_player->GetPlayerId())
	{	// A card for this player was selected/unselected
		Card* card = m_player->GetCard(cardId);
		bool validPlay = CheckForValidPlay(card);
		if (card != nullptr)
		{
			if (m_player->IsCardSelected(cardId))
			{	// The user selected this card
				// Determine if this is a valid selection
				if (!validPlay)
				{	// Invalid card selected
					// Unselect it
					m_player->SetCardSelection(cardId, false);
				}
				// else, valid card selection
			}
			// else, the card was unselected

			if (validPlay && (m_player->GetNumOfSelectedCards() == 1))
			{	// Only 1 card is selected and it's valid
				ui->buttonBox->setEnabled(true);		// enable the OK button
				m_cardId = cardId;									// This is the card we'll return if the user hits ok
			}
			else
			{	// Invalid # of cards selected
				ui->buttonBox->setEnabled(false);
			}
		}
	}
	// else, there isn't a valid card here. Ignore.
}

void selectCardDialog::on_buttonBox_accepted()
{
	emit CardSelectionComplete(m_cardId);
}

bool selectCardDialog::CheckForValidPlay(Card* cardToCheck)
{
	if (m_leadCard == nullptr)
	{	// No card has been led
		// Any play is valid
		return true;
	}
	else
	{
		/* The player has to follow the suit of the lead card.
		 * If they don't have any of that suit, any card is valid.
		 */
		auto leadSuit = m_player->GetTrumpSuit(m_leadCard, m_trumpSuit);
		auto selectedCardSuit = m_player->GetTrumpSuit(cardToCheck, m_trumpSuit);

		if (leadSuit == selectedCardSuit)
		{	// Player is following suit
			return true;
		}
		else
		{	// Player is not following suit
			if (m_player->GetSuitCount(leadSuit) > 0)
			{	// Invalid play. The player has the cards to follow suit.
				return false;
			}
			else
			{	// Player doesn't have the lead suit. They can play any card.
				return true;
			}
		}
	}
}
