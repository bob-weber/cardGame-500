#ifndef MERGECARDS_H
#define MERGECARDS_H

#include <QWidget>
#include "player.h"
#include "card.h"

class MergeCards : public QWidget
{
		Q_OBJECT

	public:
		explicit MergeCards(Player *player, Player *kitty, QWidget *parent = nullptr);

	public slots:
		//void CardSelected(uint playerId, uint cardIndex);
		//void Start();

	signals:
		void finished();

	public slots:

	private:
		Player *m_player;
		Player *m_ktty;

};

#endif // MERGECARDS_H
