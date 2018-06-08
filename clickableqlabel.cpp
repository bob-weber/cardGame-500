#include "clickableqlabel.h"

ClickableQLabel::ClickableQLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ClickableQLabel::~ClickableQLabel() {}

void ClickableQLabel::mousePressEvent(QMouseEvent* event)
{
	typedef struct {
		QString labelName;
		uint player;
		uint card;
	} playerCardLookupT;

	// Map a player and card index to each clickable card label
	const playerCardLookupT playerCardLookup[45] = {
	  { "lbl_P1C1",  0,  0 },
	  { "lbl_P1C2",  0,  1 },
	  { "lbl_P1C3",  0,  2 },
	  { "lbl_P1C4",  0,  3 },
	  { "lbl_P1C5",  0,  4 },
	  { "lbl_P1C6",  0,  5 },
	  { "lbl_P1C7",  0,  6 },
	  { "lbl_P1C8",  0,  7 },
	  { "lbl_P1C9",  0,  8 },
	  { "lbl_P1C10", 0,  9 },

	  { "lbl_P2C1",  1,  0 },
	  { "lbl_P2C2",  1,  1 },
	  { "lbl_P2C3",  1,  2 },
	  { "lbl_P2C4",  1,  3 },
	  { "lbl_P2C5",  1,  4 },
	  { "lbl_P2C6",  1,  5 },
	  { "lbl_P2C7",  1,  6 },
	  { "lbl_P2C8",  1,  7 },
	  { "lbl_P2C9",  1,  8 },
	  { "lbl_P2C10", 1,  9 },

	  { "lbl_P3C1",  2,  0 },
	  { "lbl_P3C2",  2,  1 },
	  { "lbl_P3C3",  2,  2 },
	  { "lbl_P3C4",  2,  3 },
	  { "lbl_P3C5",  2,  4 },
	  { "lbl_P3C6",  2,  5 },
	  { "lbl_P3C7",  2,  6 },
	  { "lbl_P3C8",  2,  7 },
	  { "lbl_P3C9",  2,  8 },
	  { "lbl_P3C10", 2,  9 },

	  { "lbl_P4C1",  3,  0 },
	  { "lbl_P4C2",  3,  1 },
	  { "lbl_P4C3",  3,  2 },
	  { "lbl_P4C4",  3,  3 },
	  { "lbl_P4C5",  3,  4 },
	  { "lbl_P4C6",  3,  5 },
	  { "lbl_P4C7",  3,  6 },
	  { "lbl_P4C8",  3,  7 },
	  { "lbl_P4C9",  3,  8 },
	  { "lbl_P4C10", 3,  9 },

	  { "lbl_KittyC1",  4,  0 },
	  { "lbl_KittyC2",  4,  1 },
	  { "lbl_KittyC3",  4,  2 },
	  { "lbl_KittyC4",  4,  3 },
	  { "lbl_KittyC5",  4,  4 },
	};

	QString name = this->objectName();
	for (uint i = 0; i < 45; i++)
	{
		if (playerCardLookup[i].labelName == name)
		{	// Found the correct player/card
			emit clicked(playerCardLookup[i].player, playerCardLookup[i].card);
			break;
		}
		// else, not the correct label
	}
}
