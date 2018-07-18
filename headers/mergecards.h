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
		void StartMerge(Player* player, Player* kitty);

	public slots:
		void UpdateCardSelection();
		void CompleteMerge();
		void ResetMerging();

	signals:
		void CheckSelectedNumOfCards(uint numOfPlayerCardsSelected, uint numOfKittyCardsSelected);
		void MergingComplete();

	private:
		Player *m_player;
		Player *m_kitty;

		// Pointer to msg box, so other functions
		QMessageBox* m_mergeMsgBox;
};

#endif // MERGECARDS_H
