#ifndef TEST_SCORE_H
#define TEST_SCORE_H

#include <QObject>
#include "../../headers/score.h"

class test_Score : public QObject
{
		Q_OBJECT
	public:
		explicit test_Score(QObject *parent = nullptr);

	signals:

	public slots:

	private Q_SLOTS:
		void verifyScore();
		void verifyUpdateScore();
};

#endif // TEST_SCORE_H
