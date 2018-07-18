#ifndef SCORE_H
#define SCORE_H

#include <QObject>

#include "game_500_settings.h"
#include "bid.h"
/**********************************************************************************************************************
 * This class manages the bidding score and team scores.
 **********************************************************************************************************************/

class Score : public QObject
{
		Q_OBJECT

	public:
		/******************************************************************************************************************
		 * Constructor for the class. Clears all scores when a new instance is created.
		 *
		 * Inputs
		 *	None
		 *
		 * Outputs:
		 *	m_teamScore is initialized.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		explicit Score(QObject *parent = nullptr);

		/******************************************************************************************************************
		 * Clears the scoring for all teams.
		 *
		 * Inputs
		 *	None
		 *
		 * Outputs:
		 *	m_teamScore is set to 0 for each team.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void ClearTeamScores();

		/******************************************************************************************************************
		 * Update the scoring for the specified team.
		 * If a team has won the bid, their score will be added to, or subracted from, by the scoring value of the bid.
		 *
		 * If a team did not win the bid, they will get 10 points for each trick they took, if it was a suit bid, or
		 * 10 points for each trick the bidding team took, if it was a nellow bid.
		 *
		 * Inputs
		 *	teamID:				Team identifier
		 *	numOfTricks:	Number of tricks the team bid, or if not the bidding team, number of tricks they took/gave.
		 *  bidSuit:			The bid suit of the bid, or nellow.
		 *	success:			true if the bid was successful; false if not.
		 *
		 * Outputs:
		 *	m_teamScore is updated for the specified team.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		void UpdateBiddingScore(uint teamId, uint numOfTricks, Bid::bidSuitT bidSuit, bool success);
		void updateNonbiddingScore(uint teamId, uint numOfTricks);

		/******************************************************************************************************************
		 * Get the scoring value of the specified bid.
		 *
		 * Inputs
		 *	numOfTricks:	The number of tricks for the bid.
		 *  bidSuit:			The bid suit, or nellow.
		 *
		 * Outputs:
		 *	Returns the scoring value of the bid.
		 *
		 * Notes:
		 ******************************************************************************************************************/
		uint GetBidScore(uint numOfTricks, Bid::bidSuitT bidSuit);

		/******************************************************************************************************************
		 * Get the score for the specified team
		 *
		 * Inputs
		 *	teamId:		Team Id
		 *
		 * Outputs:
		 *	Returns the team score.
		 *
		 * Notes:	If team ID is invalid, 0 is returned. No error is indicated.
		 ******************************************************************************************************************/
		int GetTeamScore(uint teamId);


	signals:

	public slots:

	private:
		// Scoring for current bids
		static const int bidScore[Bid::BID_NUM_OF_SUITS][NUM_OF_CARDS_PER_PLAYER];

		// Team scores. Only one set of scores for the game.
		static int m_teamScore[NUM_OF_TEAMS];
};

#endif // SCORE_H
