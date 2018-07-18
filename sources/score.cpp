#include <QObject>
#include "../headers/game_500_settings.h"
#include "../headers/bid.h"

#include "../headers/score.h"

// Initialize our static array of bidding scores
const int Score::bidScore[Bid::BID_NUM_OF_SUITS][NUM_OF_CARDS_PER_PLAYER] =
{	//   1    2    3    4    5    6    7    8    9    10
  // ----  ---  ---  ---  ---  ---  ---  ---  ---  ---
  {     0,   0,   0,   0,   0,  40, 140, 240, 340, 440 },	// Spades bid
  {     0,   0,   0,   0,   0,  60, 160, 260, 360, 460 },	// Clubs bid
  {     0,   0,   0,   0,   0,  80, 180, 280, 380, 480 },	// Diamonds bid
  {     0,   0,   0,   0,   0, 100, 200, 300, 400, 500 },	// Hearts bid
  {     0,   0,   0,   0,   0, 120, 220, 320, 420, 520 },	// No Trump bid
  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 250 },	// Nellow bid
  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 500 },	// Open nellow bid
  {     0,   0,   0,   0,   0,   0,   0,   0,   0, 500 },	// Double nellow bid
};

int Score::m_teamScore[NUM_OF_TEAMS] = { 0, 0 };

Score::Score(QObject *parent) : QObject(parent)
{
}

void Score::ClearTeamScores()
{
	m_teamScore[0] = 0;
	m_teamScore[1] = 0;
}

void Score::UpdateBiddingScore(uint teamId, uint numOfTricks, Bid::bidSuitT bidSuit, bool success)
{
	if (success)
	{	// Team succeeded in their bid. Add the bid value to their score.
		m_teamScore[teamId] += GetBidScore(numOfTricks, bidSuit);
	}
	else
	{	// Team failed. Subtract the bid value from their score.
		m_teamScore[teamId] -= GetBidScore(numOfTricks, bidSuit);
	}
}

void Score::updateNonbiddingScore(uint teamId, uint numOfTricks)
{
	m_teamScore[teamId] += (10 * numOfTricks);
}

uint Score::GetBidScore(uint numOfTricks, Bid::bidSuitT bidSuit)
{
	uint score = 0;
	if ((numOfTricks > 0) && (numOfTricks <= NUM_OF_CARDS_PER_PLAYER) &&
	    (bidSuit < Bid::BID_NUM_OF_SUITS))
	{
		// Note that the scoring table has no entry for 0 tricks. It starts at 1, so we need to -1 from # of tricks.
		score = bidScore[bidSuit][numOfTricks-1];
	}
	return score;
}

int Score::GetTeamScore(uint teamId)
{
	uint score = 0;
	if (teamId < NUM_OF_TEAMS)
	{
		score = m_teamScore[teamId];
	}
	return score;
}
