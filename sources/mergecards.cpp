#include "mergecards.h"

MergeCards::MergeCards(Player *player, Player *kitty, QWidget *parent)
{
	// Save pointers to the 2 players we're merging cards with
	m_player = player;
	m_ktty = kitty;

}
