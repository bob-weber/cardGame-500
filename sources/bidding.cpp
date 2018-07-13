#include <QMessageBox>
#include <QString>

#include "utilities.h"
#include "game_settings.h"
#include "user_bid_dialog.h"
#include "score.h"
#include "player.h"

#include "bidding.h"

Bidding::Bidding(QObject *parent) : QObject(parent)
{
	m_highestBid = new Bid();
	m_highestBid->Clear();	// Reset the current bid. Clean slate.
}

Bidding::~Bidding()
{
	delete m_highestBid;
}

void Bidding::GetAllBids(uint dealer, Player** players)
{
	// Save pointers to the structures we'll need to do the bidding
	m_bidder = dealer;
	m_players = players;

	// Initialize the position of the dialog box
	// TODO: It'd be nice to save this to the file system, so it survives bids in later hands, and game restarts.
	m_biddingDialogPosition.setX(0);
	m_biddingDialogPosition.setY(0);

	// Set all player actions to waiting to bid
	QString bidMsg = QString("Waiting");
	for (uint i=0; i < NUM_OF_PLAYERS; i++)
	{
		emit PlayerActionChanged(i, bidMsg);
	}
	// Identify the dealer
	emit PlayerActionChanged(m_bidder, "Dealer, Waiting");

	// Get a bid for each player
	m_nellowTeamId = NUM_OF_PLAYERS;	// invalid Id
	m_completedBidCount = 0;

	// start bidding to the left of the dealer
	m_bidder = advanceIndex(m_bidder, NUM_OF_PLAYERS);

	// Get this player's bid
	GetOneBid();
}

void Bidding::GetOneBid()
{
	// Update the player status on the GUI
	Player *player = m_players[m_bidder];
	emit PlayerActionChanged(m_bidder, "Bidding");

	// Dialog to get the user bid
	// Make it non-modal so the user can interface with the tabletop
	UserBidDialog *dialog = new UserBidDialog(m_bidder, player->GetPlayerName());
	dialog->setModal(false);
	dialog->move(m_biddingDialogPosition);

	// connect this object's signals
	connect(dialog, &UserBidDialog::PlayerHasBid, this, &Bidding::VerifyPlayerBid);
	connect(dialog, &UserBidDialog::DialogPositionChanged, this, &Bidding::SaveDialogPosition);

	// When the dialog completes, it'll call BiddingIsComplete();
	dialog->show();
	dialog->raise();
	dialog->activateWindow();
}

void Bidding::VerifyPlayerBid(Bid* playerBid)
{
	Score score;		// Used for scoring the bid
	uint playerBidScore = score.GetBidScore(playerBid->GetNumOfTricks(), playerBid->GetBidSuit());
	uint currentBidScore = score.GetBidScore(m_highestBid->GetNumOfTricks(), m_highestBid->GetBidSuit());
	Player *player = m_players[m_bidder];

	bool validBidOrPass = false;
	if (playerBid->IsValid())
	{	// The player bid something
		uint playerId = playerBid->GetPlayerId();
		uint teamId = m_players[playerId]->GetTeamId();

		if (playerBidScore > currentBidScore)
		{	// This bid is > than our current bid
			if (playerBid->GetBidSuit() == Bid::BID_NELLOW)
			{	// Save nellow bid info in case someone later bids double nellow
				/* We don't need to verify nellow hasn't already been bid in this round
				 * because if it had, bidScore wouldn't be > the current score.
				 */
				validBidOrPass = true;
				m_nellowTeamId = teamId;
			}
			else if (playerBid->GetBidSuit() == Bid::BID_DOUBLE_NELLOW)
			{
				// Double nellow is only valid if partner bid nellow
				if (player->GetTeamId() == m_nellowTeamId)
				{	// This is a valid double nellow bid
					validBidOrPass = true;
				}
				else
				{	// Invalid double nellow bid
					QMessageBox msgBox;
					QString msg = QString("%1, your bid of %2 is invalid.")
					    .arg(player->GetPlayerName()).arg(playerBid->GetBidText());
					QString informativeMsg = QString("%1 requires your parter bid Nellow.\n\rSelect Ok to re-bid.")
					    .arg(playerBid->GetBidText());
					msgBox.setText(msg);
					msgBox.setInformativeText(informativeMsg);
					msgBox.setStandardButtons(QMessageBox::Ok);
					msgBox.setDefaultButton(QMessageBox::Ok);
					msgBox.exec();
					// validBidOrPass == false will result in user rebidding
				}
				// else, invalid double nellow bid
			}
			else
			{	// Valid suit/# of tricks bid
				validBidOrPass = true;
			}
		}
		else
		{	// Bid score is too low
			QMessageBox msgBox;
			QString msg = QString("%1, your bid of %2 is invalid.")
			    .arg(player->GetPlayerName()).arg(playerBid->GetBidText());
			QString informativeMsg = QString("The current game bid is %1, and has a score of %2.\nThe score of your bid is %3.\n\rSelect Ok to Pass on bidding, or select Cancel to re-bid.")
			    .arg(m_highestBid->GetBidText()).arg(currentBidScore).arg(playerBidScore);
			msgBox.setText(msg);
			msgBox.setInformativeText(informativeMsg);
			msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			int ret = msgBox.exec();
			if (ret == QMessageBox::Ok)
			{	// The user has accepted a "Pass"
				playerBid->Clear();
				// We're done
				validBidOrPass = true;
				emit PlayerActionChanged(m_bidder, "Bid: Passed");
			}
			else
			{	// User has cancelled, meaning they want to rebid
				// Mark this bid as invalid
				validBidOrPass = false;
			}
		}
	}
	else
	{	// No bid, Pass
		validBidOrPass = true;
		emit PlayerActionChanged(m_bidder, "Bid: Passed");
	}

	if (validBidOrPass)
	{	// A valid bid, or a valid pass
		if (playerBid->IsValid())
		{	// This is a bid with a score, not a pass, and it's > the current bid
			if (m_highestBid->IsValid())
			{	// The current bid is also valid, so this is a new, higher bid than the current bid.
				// Set the prior bid winner's action to "Outbid"
				emit PlayerActionChanged(m_highestBid->GetPlayerId(), "Bid: Outbid");
			}
			// else, this is the first valid bid. No previous bid indication to overwrite.

			// Replace the current bid
			m_highestBid = playerBid;

			// Set this player's action to their bid
			QString bidMsg = QString("Bid: %1").arg(m_highestBid->GetBidText());
			emit PlayerActionChanged(m_highestBid->GetPlayerId(), bidMsg);
		}
		// else, this player passed

		// This player is done. Advance to the next player
		++m_completedBidCount;
		if (m_completedBidCount < NUM_OF_PLAYERS)
		{	// We're not done
			// Advance the bidder and start a new bid
			m_bidder = advanceIndex(m_bidder, NUM_OF_PLAYERS);
			GetOneBid();
		}
		else
		{	// Done getting bids for all players
			emit BiddingIsComplete(m_highestBid);
		}
	}
	else
	{	// Not a valid bid or pass
		// Do not advance he bidder, and get a new bid for this player
		GetOneBid();
	}
}


void Bidding::SaveDialogPosition(QPoint position)
{
	m_biddingDialogPosition = position;
}
