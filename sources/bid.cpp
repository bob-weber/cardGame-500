#include <QWidget>
#include "game_settings.h"

#include "bid.h"

const QString Bid::m_bidSuitText[BID_NUM_OF_SUITS] = {
  "Spades", "Clubs", "Diamonds", "Hearts", "No Trump", "Nellow", "Open Nellow", "Double Nellow"
};

Bid::Bid(uint playerId, uint numOfTricks, bidSuitT suit, QObject *parent) : QObject(parent)
{
	this->m_playerId = playerId;
	this->m_numOfTricks = numOfTricks;
	this->m_bidSuit = suit;
}

uint Bid::GetPlayerId() const {
	return this->m_playerId;
}

void Bid::SetPlayerId(uint Id)
{
	this->m_playerId = Id;
}

uint Bid::GetNumOfTricks() const {
	return this->m_numOfTricks;
}

void Bid::SetNumOfTricks(uint numOfTricks)
{
	this->m_numOfTricks = numOfTricks;
}


Bid::bidSuitT Bid::GetBidSuit() const {
	return this->m_bidSuit;
}

void Bid::SetBidSuit(bidSuitT bidSuit)
{
	this->m_bidSuit = bidSuit;
}

QString Bid::GetSuitText()
{
	QString bidSuitStr = "";
	if (m_bidSuit < BID_NUM_OF_SUITS)
	{	// This is a valid bidding suit
		bidSuitStr.append(m_bidSuitText[m_bidSuit]);
	}
	return bidSuitStr;
}

QString Bid::GetBidText()
{
	QString bidStr = "";
	if (IsValid())
	{	// We have a valid bid
		if ((m_bidSuit >= BID_NELLOW) && (m_bidSuit <= BID_DOUBLE_NELLOW))
		{	// This is a nellow bid
			bidStr.append(m_bidSuitText[m_bidSuit]);
		}
		else
		{	// This is a suit bid, with a number of tricks specified
			QString suitBidStr = QString("%1 %2").arg(m_numOfTricks).arg(m_bidSuitText[m_bidSuit]);
			bidStr.append(suitBidStr);
		}
	}
	// else, the bid is invalid. Return an empty string.
	return bidStr;
}

bool Bid::IsValid()
{
	bool validBid = (m_playerId < NUM_OF_PLAYERS) &&
	                (m_bidSuit < BID_NUM_OF_SUITS) &&
	                (m_numOfTricks > 0) && (m_numOfTricks <= NUM_OF_CARDS_PER_PLAYER);
	return validBid;
}

void Bid::Clear()
{
	m_playerId = NUM_OF_PLAYERS;
	m_numOfTricks = 0;
	m_bidSuit = BID_NUM_OF_SUITS;
}
