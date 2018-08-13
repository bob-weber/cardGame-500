#ifndef PLAYCARDS_H
#define PLAYCARDS_H

#include <QObject>

#include "player.h"
#include "bid.h"
#include "card.h"
#include "utilities.h"

class PlayCards : public QObject
{
		Q_OBJECT

	public:
		/******************************************************************************************************************
		 * This constructor saves key values needed to play a hand.
		 *
		 * Inputs:
		 *	 m_players:	The player objects
		 *   bid:			  The bid for this hand.
		 *
		 * Outputs:
		 *	 m_players:	A list of players who're playing this hand.
		 *	 m_leadPlayer:	Lead player, the winning bidder.
		 *	 m_bid:					Bid for this hand.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		explicit PlayCards(Player **m_players, Bid *bid, QObject *parent = nullptr);

		/******************************************************************************************************************
		 * This function prepares to play a hand of cards. It set's up the GUI, and then creates a list of players
		 * that play this hand (some bids result in a player sitting out).
		 *
		 * Inputs:
		 *	m_players: The player objects
		 *
		 * Outputs:
		 *	 m_activePlayers:	A list of players who're playing this hand.
		 *	 m_numOfHandsBeingPlayed: Number of players playing.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void PlayHand();

	signals:
		/******************************************************************************************************************
		 * This signal is emitted when a round has been completed; all players have selected the cards to play.
		 *
		 * Outputs:
		 *   None
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void SelectCardsComplete();

		/******************************************************************************************************************
		 * Signal passed to the card selection dialog when the user selects a card on the GUI.
		 *
		 * Outputs:
		 *	 playerId:	Player Id of the selected card.
		 *   cardId:	Card position
		 * Notes:
		 ******************************************************************************************************************/
		void CardSelectionChanged(uint playerId, uint cardId);

	public slots:
		/******************************************************************************************************************
		 * This slot is called when the user is done selecting a card to play.
		 * It records which card was played and moves it to the the play area.
		 * It advances to the next player to select a card, or if this is the last player, scores the round.
		 *
		 * Inputs:
		 *	selectedCardId:	Position of the selected card.
		 *
		 * Outputs:
		 *	m_playedCards[]: Record of what card was played
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void PlaySelectedCard(uint selectedCardId);

		/******************************************************************************************************************
		 * This slot is called from the GUI when a card is selected. It emits the CardSelectionChanged signal to pass this
		 * onto the card selection dialog.
		 *
		 * Inputs:
		 *	selectedCardId:	Position of the selected card.
		 *
		 * Outputs:
		 *	m_playedCards[]: Record of what card was played
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void CardSelected(uint playerId, uint cardId);

	private:
		/******************************************************************************************************************
		 * Play a round of cards for the current hand.
		 * This initializes variables that are specific to each round, and then launches SelectPlayerCard(), which handles
		 * each user selecting a card to play.
		 *
		 * Inputs:
		 *	 None
		 *
		 * Outputs:
		 *	 m_numOfPlayedCards:	Counts how many players have played
		 *	 m_currentPlayerIt:	  Iterator for moving through the active player's list.
		 *
		 * Exceptions:
		 * Notes:
		 ******************************************************************************************************************/
		void PlayRound();

		/******************************************************************************************************************
		 * Present the specified player with a pop-up, allowing them to select a card.
		 * Only valid moves are selectable.
		 *
		 * Inputs
		 *	 m_currentPlayerIt:	Iterator for the current player.
		 *	 m_bid:	Current bid. Needed to determine the trump suit, which affects which cards are trump.
		 *	 m_leadCard: The lead card. This is null for the 1st player in a round, but is valid after that.
		 *	 This affects which cards are valid plays for the players following the lead.
		 *
		 * Outputs
		 *	 None
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void SelectPlayerCard();

		/******************************************************************************************************************
		 * TODO
		 *
		 * Inputs
		 *
		 * Outputs
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void ScoreRound();

		Player **m_players;			// All the players
		uint m_leadPlayer;			// The player that starts play for a round

		Bid *m_bid;							// The current bid
		Card* m_leadCard;				// The first suit played in a round

		list<uint> m_activePlayers;	// List of player's who play a hand
		list<uint>::iterator m_currentPlayerIt;	// Iterator that points to the current player

		uint m_numOfHandsBeingPlayed;		// For this bid, how many players are playing
		uint m_numOfPlayedCards;				// How many players have played this round

		Card* m_playedCards[NUM_OF_PLAYERS];	// The cards played in a given round
		// uint m_numOfPlayedSuits[Card::SUIT_NUMBER_OF_SUITS];

		// A bit-packed array that tracks each card played.
		// uint32_t IsCardPlayed[Card::SUIT_NUMBER_OF_SUITS];

};

#endif // PLAYCARDS_H
