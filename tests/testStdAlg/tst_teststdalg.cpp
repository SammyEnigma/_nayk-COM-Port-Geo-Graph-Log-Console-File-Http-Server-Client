#include <QtTest>
#include <QByteArray>
#include "std_alg.h"

using namespace nayk;

// add necessary includes here
//==================================================================================================
class testStdAlg : public QObject
{
    Q_OBJECT

public:
    testStdAlg();
    ~testStdAlg();

private:
    QByteArray arr1 {"qca37b1nr4jdpm0i8ks6h2etl5o9fg"};
    QByteArray arr2 {"0123456789abcdefghijklmnopqrst"};
    QByteArray arr3 {"tsrqponmlkjihgfedcba9876543210"};

private slots:
    void initTestCase();
    void cleanupTestCase();
    //
    void test_sort_Bubble();
    void test_sort_Insertion();
    void test_sort_Quick();
    void test_sort_Merge();
};
//==================================================================================================
testStdAlg::testStdAlg()
{

}
//==================================================================================================
testStdAlg::~testStdAlg()
{

}
//==================================================================================================
void testStdAlg::initTestCase()
{

}
//==================================================================================================
void testStdAlg::cleanupTestCase()
{

}
//==================================================================================================
void testStdAlg::test_sort_Bubble()
{
    QByteArray tmp = arr1;
    QBENCHMARK( Algorithm::sort(tmp, Algorithm::BubbleSort, Algorithm::SortAsc) );
    QCOMPARE( tmp, arr2 );

    tmp = arr1;
    Algorithm::sort(tmp, Algorithm::BubbleSort, Algorithm::SortDesc);
    QCOMPARE( tmp, arr3 );
}
//==================================================================================================
void testStdAlg::test_sort_Insertion()
{
    QByteArray tmp = arr1;
    QBENCHMARK( Algorithm::sort(tmp, Algorithm::InsertionSort, Algorithm::SortAsc) );
    QCOMPARE( tmp, arr2 );

    tmp = arr1;
    Algorithm::sort(tmp, Algorithm::InsertionSort, Algorithm::SortDesc);
    QCOMPARE( tmp, arr3 );
}
//==================================================================================================
void testStdAlg::test_sort_Quick()
{
    QByteArray tmp = arr1;
    QBENCHMARK( Algorithm::sort(tmp, Algorithm::QuickSort, Algorithm::SortAsc) );
    QCOMPARE( tmp, arr2 );

    tmp = arr1;
    Algorithm::sort(tmp, Algorithm::QuickSort, Algorithm::SortDesc);
    QCOMPARE( tmp, arr3 );
}
//==================================================================================================
void testStdAlg::test_sort_Merge()
{
    QByteArray tmp = arr1;
    QBENCHMARK( Algorithm::sort(tmp, Algorithm::MergeSort, Algorithm::SortAsc) );
    QCOMPARE( tmp, arr2 );

    tmp = arr1;
    Algorithm::sort(tmp, Algorithm::MergeSort, Algorithm::SortDesc);
    QCOMPARE( tmp, arr3 );
}
//==================================================================================================

//==================================================================================================

QTEST_APPLESS_MAIN(testStdAlg)

#include "tst_teststdalg.moc"
