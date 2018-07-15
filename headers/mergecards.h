#ifndef MERGECARDS_H
#define MERGECARDS_H

#include <QObject>
#include <QMessageBox>

#include "player.h"
#include "card.h"

class MergeCards : public QObject
{
		Q_OBJECT

	public:
		explicit MergeCards(QObject *parent = nullptr);

	public slots:
		void MergeHands(Player* player, Player* kitty);

	signals:
		void MergingComplete();

	public slots:
		//void CardSelectionChanged(uint playerId, bool cardIsRaised);

	private:
		Player *m_player;
		Player *m_kitty;

		// Keep a count of the number of selected cards in the player's hand and the kitty.
		uint m_kittySelectedCardsCount;
		uint m_playerSelectedCardsCount;

		// Pointer to msg box, so other functions
		QMessageBox* m_mergeMsgBox;
};

#endif // MERGECARDS_H
