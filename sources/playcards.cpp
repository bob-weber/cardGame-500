#include "player.h"
#include "card.h"
#include "selectCardDialog.h"
#include "game_500_settings.h"
#include "mainwindow.h"
#include "logic.h"

#include "playcards.h"

PlayCards::PlayCards(Player **players, Bid *bid, QObject *parent) : QObject(parent)
{
	m_players = players;
	m_leadPlayer = bid->GetPlayerId();
	m_bid = bid;
}

void PlayCards::PlayHand()
{
	/* Setup the table. This means:
	 * clear all selected cards
	 * Turn all player's cards face down
	 * Remove any cards from the kitty
	 * Clear the kitty. This is for playing cards now.
	 */
	for (uint playerId = 0; playerId < NUM_OF_PLAYERS; playerId++)
	{
		m_players[playerId]->DeselectAllCards();
		m_players[playerId]->SetHandOrietation(Card::FACE_DOWN);
	}
	m_players[KITTY_INDEX]->RemoveAllCards();

	m_leadCard = nullptr;		// No lead card until the first player plays a card.

	/* Create a list of player's who play this hand, in the order they play
	 * Either all 4 players play, or in the case of nellow or open nellow,
	 * 3 players play. The winning bidder's partner does not play in these cases.
	 *
	 * Create a list of players who play this hand. This will not change for a given
	 * hand, but will change for different hands with different bids, so we create this
	 * each time we play a hand.
	 *
	 * First player to play is the bidder. After that, it moves to the person who took
	 * the trick. Since we need to be able to start in the sequence at a different spot
	 * depending on who won the bid. We could use a list or a vector. With either, when
	 * it's time to start a new hand, we need to search the list/vector for the position
	 * to start the hand by checking the player ID, since we don't want to presume where
	 * that player may be in the sequence. Since random access doesn't seem to buy us anything
	 * we'll use a list.
	 */

	uint activePlayer = m_bid->GetPlayerId();
	m_numOfHandsBeingPlayed = NUM_OF_PLAYERS;			// Assume every player plays, initially

	// Add the bidder as the first player to play
	m_activePlayers.clear();		// Remove any current players
	m_activePlayers.push_back(activePlayer);
	activePlayer = advanceIndex(activePlayer, NUM_OF_PLAYERS);

	// Add the player after the bidder
	m_activePlayers.push_back(activePlayer);
	activePlayer = advanceIndex(activePlayer, NUM_OF_PLAYERS);

	// Add the bidder's partner if it's not a nellow bid
	if ((m_bid->GetBidSuit() == Bid::BID_NELLOW) ||
	    (m_bid->GetBidSuit() == Bid::BID_OPEN_NELLOW))
	{	// This bid plays without a partner
		// Skip the bidder's partner, and update theh playing count
		m_numOfHandsBeingPlayed = 3;
	}
	else
	{	// All 4 players play
		m_activePlayers.push_back(activePlayer);
	}
	activePlayer = advanceIndex(activePlayer, NUM_OF_PLAYERS);

	// Add the final player
	m_activePlayers.push_back(activePlayer);

	PlayRound();
}

void PlayCards::PlayRound()
{
	// This is the start of a new round of play for this hand
	m_numOfPlayedCards = 0;
	m_currentPlayerIt = m_activePlayers.begin();
	SelectPlayerCard();

}
void PlayCards::SelectPlayerCard()
{
	Player* player = m_players[*m_currentPlayerIt];
	player->DeselectAllCards();	// Start with no cards selected
	player->SetHandOrietation(Card::FACE_UP);

	// Dialog to let player select the card
	// Make it non-modal so the user can interface with the tabletop
	selectCardDialog* selectCard = new selectCardDialog(player, m_bid->GetBidSuit(), m_leadCard);

	// connect this object's signals
	connect(selectCard, &selectCardDialog::CardSelectionComplete, this, &PlayCards::PlaySelectedCard);
	connect(this, &PlayCards::CardSelectionChanged, selectCard, &selectCardDialog::CardSelected);

	// When the dialog completes, it'll call SelectCardComplete();
	selectCard->show();
	selectCard->raise();
	selectCard->activateWindow();
}

void PlayCards::PlaySelectedCard(uint selectedCardId)
{
	// The player has selected the card to play.
	// Save it to the list of played cards.
	Player* player = m_players[*m_currentPlayerIt];
	Card* playedCard = player->GetCard(selectedCardId);
	m_playedCards[*m_currentPlayerIt] = playedCard;

	// Move the selected card to this player's center table location
	player->SetCard(selectedCardId, nullptr);	// Clear card in the hand
	player->RefreshHand();										// Update the cards on the GUI
	m_players[PLAY_AREA_INDEX]->SetCard(*m_currentPlayerIt, playedCard);	// Show it in the play area
	m_players[PLAY_AREA_INDEX]->RefreshHand();

	// Deselect and turn face down this player's cards
	player->DeselectAllCards();
	player->SetHandOrietation(Card::FACE_DOWN);

	++m_numOfPlayedCards;
	if (m_numOfPlayedCards == 1)
	{	// This was the first play of the round
		m_leadCard = playedCard;		// This sets the lead suit
	}
	// else, not the lead player

	if (m_numOfPlayedCards >= m_numOfHandsBeingPlayed)	// All hands have played this round
	{	// See who won the hand
		ScoreRound();
		// TODO: Choose the new round leader
	}
	else
	{	// Not the last player
		// Get the next player and play the next round
		m_currentPlayerIt++;
		if (m_currentPlayerIt == m_activePlayers.end())
		{	// Last player in the list
			// Start over
			m_currentPlayerIt = m_activePlayers.begin();
		}
		// else, not at the end of the list

		// This round isn't over. Get the next player's card.
		SelectPlayerCard();
	}
}

void PlayCards::ScoreRound()
{
	for (uint trickId = 0; trickId < NUM_OF_PLAYERS; trickId++)
	{
		Card* card = m_playedCards[trickId];
		if (card != nullptr)
		{

		}
	}
}


void PlayCards::CardSelected(uint playerId, uint cardId)
{
	// Pass this signal onto the dialog
	emit CardSelectionChanged(playerId, cardId);
}

