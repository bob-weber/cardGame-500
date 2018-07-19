#include <QObject>
#include <QMessageBox>

#include "game_500_settings.h"
#include "card.h"
#include "player.h"
#include "mergeDialog.h"

#include "mergecards.h"

MergeCards::MergeCards(QObject *parent)
{
	Q_UNUSED(parent);
}

void MergeCards::StartMerge(Player* player, Player* kitty)
{
	m_player = player;
	m_kitty = kitty;

	// Turn face-up every card in the players hand and kitty
	for (uint cardIndex = 0; cardIndex < NUM_OF_CARDS_PER_PLAYER; cardIndex++)
	{
		m_player->SetCardOrientation(cardIndex, Card::FACE_UP);
	}
	for (uint cardIndex = 0; cardIndex < NUM_OF_CARDS_IN_KITTY; cardIndex++)
	{
		m_kitty->SetCardOrientation(cardIndex, Card::FACE_UP);
	}

	/* Pop up a dialog that explains how to merge the hand with the kitty.
	 * It contains an Ok and Reset button.
	 * Ok - the player is done merging the hand with the kitty. This is disabled unless the number of cards selected in
	 *      player's hand is the same as those selected in the kitty.
	 * Reset - Unselect all the cards and start over.
	 *
	 * When Ok is selected (and it's enabled), the selected cards in the kitty are exchanged with those selected in the
	 * player's hand.
	 */

	// Dialog to merge cards
	// Make it non-modal so the user can interface with the tabletop
	MergeDialog *mergeDialog = new MergeDialog(m_player->GetNumOfSelectedCards(), m_kitty->GetNumOfSelectedCards());
	mergeDialog->setModal(false);

	// connect this object's signals
	//connect(this, &MergeCards::UpdateCardSelection,  mergeDialog, &MergeDialog::ControlOkButton);
	connect(this, &MergeCards::CheckSelectedNumOfCards, mergeDialog, &MergeDialog::CheckSelectedNumOfCards);
	connect(mergeDialog, &MergeDialog::ClearSelectedCards, this, &MergeCards::ResetMerging);
	connect(mergeDialog, &MergeDialog::CardSelectionComplete, this, &MergeCards::CompleteMerge);

	// When the dialog completes, it'll call BiddingIsComplete();
	mergeDialog->show();
	mergeDialog->raise();
	mergeDialog->activateWindow();
}


void MergeCards::CompleteMerge()
{
	if (m_player->GetNumOfSelectedCards() == m_kitty->GetNumOfSelectedCards())
	{
		// Exchange the selected cards
		uint kittyCardId = 0;
		for (uint playerCardId = 0; playerCardId < NUM_OF_CARDS_PER_PLAYER; playerCardId++)
		{
			Card* playerCard = m_player->GetCard(playerCardId);
			if (playerCard != nullptr)
			{
				if (playerCard->IsSelected())
				{	// This card is selected
					// Find the next card selected in the kitty
					// Advance the kitty card index until it finds a valid, selected card
					Card* kittyCard = m_kitty->GetCard(kittyCardId);
					bool isSelected = kittyCard->IsSelected();
					while (!isSelected && (kittyCardId < NUM_OF_CARDS_IN_KITTY))
					{
						++kittyCardId;
						kittyCard = m_kitty->GetCard(kittyCardId);
						isSelected = kittyCard->IsSelected();
					}

					if (kittyCardId < NUM_OF_CARDS_IN_KITTY)
					{	// This is a selected card
						// Exchange cards
						m_player->SwapCards(playerCardId, m_kitty, kittyCardId);
						++kittyCardId;		// advance past this exchanged card
					}
					else
					{	// We didn't find a matching selected card in the kitty
						// This happens if the number of selected cards doesn't match
						// We should never get here
						cout << "Logic error, MergeCards. Didn't find matching selected card in kitty." << endl;
					}
				}
				// else, not a selected card. Ignore.
			}
			// else, no card at this location
		}

		// Sort the affected hands
		m_player->SortHand();
		m_player->RefreshHand();
		m_kitty->SortHand();
		m_kitty->RefreshHand();

		ResetMerging();
		emit MergingComplete();
	}
}

void MergeCards::ResetMerging()
{
	m_player->DeselectAllCards();
	m_kitty->DeselectAllCards();
	emit CheckSelectedNumOfCards(m_player->GetNumOfSelectedCards(), m_kitty->GetNumOfSelectedCards());
}

void MergeCards::UpdateCardSelection()
{
	emit CheckSelectedNumOfCards(m_player->GetNumOfSelectedCards(), m_kitty->GetNumOfSelectedCards());
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
