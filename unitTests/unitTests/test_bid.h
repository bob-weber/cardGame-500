#ifndef TEST_SCORE_H
#define TEST_SCORE_H

#include <QObject>
#include "../../headers/score.h"

/**********************************************************************************************************************
 * This class manages unit testing for the Score class.
 **********************************************************************************************************************/

class test_Score : public QObject
{
		Q_OBJECT
	public:
		explicit test_Score(QObject *parent = nullptr);

	signals:

	public slots:

	private Q_SLOTS:
		/******************************************************************************************************************
		 * Verify the bid scoring table.
		 ******************************************************************************************************************/
		void verifyScore();

		/******************************************************************************************************************
		 * Verify the updating and retrieving of the team score.
		 * Verify the scoring logic is static.
		 ******************************************************************************************************************/
		void verifyUpdateScore();
};

#endif // TEST_SCORE_H
