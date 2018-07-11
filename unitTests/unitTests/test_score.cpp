#include <QtTest>

#include "../../headers/score.h"
#include "../../headers/bid.h"

#include "test_score.h"

test_Score::test_Score(QObject *parent) : QObject(parent)
{
	verifyScore();
	verifyUpdateScore();
}

void test_Score::verifyScore()
{
	// Verify we ge the expected score
	Score *score = new Score();
	QVERIFY(score->GetBidScore(6,  Bid::BID_SPADES) ==  40);
	QVERIFY(score->GetBidScore(7,  Bid::BID_SPADES) == 140);
	QVERIFY(score->GetBidScore(8,  Bid::BID_SPADES) == 240);
	QVERIFY(score->GetBidScore(9,  Bid::BID_SPADES) == 340);
	QVERIFY(score->GetBidScore(10, Bid::BID_SPADES) == 440);

	QVERIFY(score->GetBidScore(6,  Bid::BID_CLUBS) == 60);
	QVERIFY(score->GetBidScore(7,  Bid::BID_CLUBS) == 160);
	QVERIFY(score->GetBidScore(8,  Bid::BID_CLUBS) == 260);
	QVERIFY(score->GetBidScore(9,  Bid::BID_CLUBS) == 360);
	QVERIFY(score->GetBidScore(10, Bid::BID_CLUBS) == 460);

	QVERIFY(score->GetBidScore(6,  Bid::BID_DIAMONDS) == 80);
	QVERIFY(score->GetBidScore(7,  Bid::BID_DIAMONDS) == 180);
	QVERIFY(score->GetBidScore(8,  Bid::BID_DIAMONDS) == 280);
	QVERIFY(score->GetBidScore(9,  Bid::BID_DIAMONDS) == 380);
	QVERIFY(score->GetBidScore(10, Bid::BID_DIAMONDS) == 480);

	QVERIFY(score->GetBidScore(6,  Bid::BID_HEARTS) == 100);
	QVERIFY(score->GetBidScore(7,  Bid::BID_HEARTS) == 200);
	QVERIFY(score->GetBidScore(8,  Bid::BID_HEARTS) == 300);
	QVERIFY(score->GetBidScore(9,  Bid::BID_HEARTS) == 400);
	QVERIFY(score->GetBidScore(10, Bid::BID_HEARTS) == 500);

	QVERIFY(score->GetBidScore(6,  Bid::BID_NO_TRUMP) == 120);
	QVERIFY(score->GetBidScore(7,  Bid::BID_NO_TRUMP) == 220);
	QVERIFY(score->GetBidScore(8,  Bid::BID_NO_TRUMP) == 320);
	QVERIFY(score->GetBidScore(9,  Bid::BID_NO_TRUMP) == 420);
	QVERIFY(score->GetBidScore(10, Bid::BID_NO_TRUMP) == 520);

	QVERIFY(score->GetBidScore(10,  Bid::BID_NELLOW) == 250);
	QVERIFY(score->GetBidScore(10,  Bid::BID_OPEN_NELLOW) == 500);
	QVERIFY(score->GetBidScore(10,  Bid::BID_DOUBLE_NELLOW) == 500);

	// Test some erroenous inputs
	QVERIFY(score->GetBidScore(6,  Bid::BID_NELLOW) == 0);
	QVERIFY(score->GetBidScore(6,  Bid::BID_OPEN_NELLOW) == 0);
	QVERIFY(score->GetBidScore(6,  Bid::BID_DOUBLE_NELLOW) == 0);
	QVERIFY(score->GetBidScore(0,  Bid::BID_SPADES) == 0);
	QVERIFY(score->GetBidScore(1,  Bid::BID_SPADES) == 0);
	QVERIFY(score->GetBidScore(11,  Bid::BID_SPADES) == 0);
	QVERIFY(score->GetBidScore(10,  Bid::BID_NUM_OF_SUITS) == 0);
}

void test_Score::verifyUpdateScore()
{
	// Create an instance of score, and verify both teams scores are 0
	Score *score = new Score();
	QVERIFY(score->GetTeamScore(0) == 0);
	QVERIFY(score->GetTeamScore(1) == 0);

	// Update a bidding score
	score->UpdateBiddingScore(0, 6, Bid::BID_SPADES, true);
	score->UpdateBiddingScore(1, 7, Bid::BID_CLUBS, true);
	QVERIFY(score->GetTeamScore(0) ==  40);
	QVERIFY(score->GetTeamScore(1) == 160);

	// Update bidding score again, but with losing the bid
	score->UpdateBiddingScore(0, 10, Bid::BID_NELLOW, false);
	score->UpdateBiddingScore(1, 7, Bid::BID_SPADES, false);
	QVERIFY(score->GetTeamScore(0) == -210);
	QVERIFY(score->GetTeamScore(1) ==   20);

	// Update a non-bidding score
	score->updateNonbiddingScore(0, 4);
	score->updateNonbiddingScore(1, 1);
	QVERIFY(score->GetTeamScore(0) == -170);
	QVERIFY(score->GetTeamScore(1) ==   30);

	// What if we update the non-bid with 0 tricks? Shouldn't affect the score.
	score->updateNonbiddingScore(0, 0);
	QVERIFY(score->GetTeamScore(0) == -170);

	// Create a 2nd instance, and verify the score is static; retains its previous values
	Score *score2 = new Score();
	QVERIFY(score->GetTeamScore(0)  == -170);
	QVERIFY(score->GetTeamScore(1)  ==   30);
	QVERIFY(score2->GetTeamScore(0) == -170);
	QVERIFY(score2->GetTeamScore(1) ==   30);

	// Verify we can clear the scores
	// Clear via score 2, but verify with score, just to make sure the variables are static.
	score2->ClearTeamScores();
	QVERIFY(score->GetTeamScore(0) == 0);
	QVERIFY(score->GetTeamScore(1) == 0);
}
