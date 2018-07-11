#include <QString>
#include <QtTest>

#include "test_score.h"

class UnitTests : public QObject
{
		Q_OBJECT

	public:
		UnitTests();

	private Q_SLOTS:
		void initTestCase();
		void cleanupTestCase();
		void runTests_Score();
};

UnitTests::UnitTests()
{
}

void UnitTests::initTestCase()
{
}

void UnitTests::cleanupTestCase()
{
}

void UnitTests::runTests_Score()
{
	test_Score score;

	//QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UnitTests)

#include "unittests.moc"
