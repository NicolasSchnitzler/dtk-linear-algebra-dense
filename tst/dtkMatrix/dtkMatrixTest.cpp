// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#include "dtkMatrixTest.h"

#include "dtkDenseMatrix.h"

// This must match the default for PreallocSize.
static const qlonglong ExpectedMinCapacity = 0;

// Exception type that is thrown by ComplexValue.
class ComplexValueException
{
public:
    ComplexValueException(int value, bool inCtor)
        : m_value(value), m_inCtor(inCtor) {}

    int value() const { return m_value; }
    bool inConstructor() const { return m_inCtor; }

private:
    int m_value;
    bool m_inCtor;
};

// Complex type that helps the tests determine if QArray is calling
// constructors, destructors, and copy constructors in the right places.
class ComplexValue
{
public:
    enum Mode
    {
        Default,
        Init,
        Copy,
        CopiedAgain,
        Assign,
        ThrowInCtor,
        ThrowOnCopy
    };

    static int destroyCount;

    ComplexValue() : m_value(-1), m_mode(Default) {}
    ComplexValue(int value) : m_value(value), m_mode(Init) {}
#ifndef QT_NO_EXCEPTIONS
    ComplexValue(int value, Mode mode) : m_value(value), m_mode(mode)
    {
        if (mode == ThrowInCtor)
            throw new ComplexValueException(value, true);
    }
#endif
    ComplexValue(const ComplexValue& other)
        : m_value(other.m_value)
    {
        if (other.m_mode == Copy || other.m_mode == CopiedAgain)
            m_mode = CopiedAgain;
#ifndef QT_NO_EXCEPTIONS
        else if (other.m_mode == ThrowOnCopy)
            throw new ComplexValueException(other.m_value, false);
#endif
        else
            m_mode = Copy;
    }
    ~ComplexValue() { ++destroyCount; }

    ComplexValue& operator=(const ComplexValue& other)
    {
#ifndef QT_NO_EXCEPTIONS
        if (other.m_mode == ThrowOnCopy)
            throw new ComplexValueException(other.m_value, false);
#endif
        m_value = other.m_value;
        m_mode = Assign;
        return *this;
    }

    int value() const { return m_value; }
    Mode mode() const { return m_mode; }

    bool operator==(const ComplexValue& other) const
        { return m_value == other.m_value; }
    bool operator==(int other) const
        { return m_value == other; }
    bool operator!=(const ComplexValue& other) const
        { return m_value != other.m_value; }
    bool operator!=(int other) const
        { return m_value != other; }

private:
    int m_value;
    Mode m_mode;
};

int ComplexValue::destroyCount = 0;

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtkMatrixTestCase::initTestCase(void)
{

}

void dtkMatrixTestCase::init(void)
{

}

void dtkMatrixTestCase::testCreate(void)
{
    // Check the basic properties.
    dtkDenseMatrix<double> m0;

    QVERIFY(m0.isEmpty());
    QCOMPARE(m0.rowCount(), 0LL);
    QCOMPARE(m0.colCount(), 0LL);
    //QCOMPARE(m0.capacity(), ExpectedMinCapacity);
    //QVERIFY(m0.constData() == 0);

    // 
    dtkDenseMatrix<double> m1(9, 9);

    QVERIFY(!m1.isEmpty());
    QCOMPARE(m1.rowCount(), 9LL);
    QCOMPARE(m1.colCount(), 9LL);
    //QCOMPARE(m1.capacity(), qlonglong(11 * 11));
    QVERIFY(m1.constData() != 0);
    QVERIFY(m1.data() == m1.constData());
    QVERIFY(((const dtkDenseMatrix<double> *)&m1)->data() == m1.constData());

    
    double init_value = qSqrt(2);
    dtkDenseMatrix<double> m2(121, 11);
    m2.fill(init_value);



    QVERIFY(!m2.isEmpty());
    QCOMPARE(m2.rowCount(), 121LL);
    QCOMPARE(m2.colCount(), 11LL);
    QVERIFY(m2.constData() != 0);
    QVERIFY(m2.data() == m2.constData());
    QVERIFY(((const dtkDenseMatrix<double> *)&m2)->data() == m2.constData());

    for (qlonglong i = 1; i < 121 * 11; ++i)
        QCOMPARE(m2.data()[i], init_value);

    // 
    /*double init_values[4][4] = { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15} };
    dtkDenseMatrix<double, 4, 4> m3(init_values);

    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m3(i,j), init_values[i][j]);
        }
    }

    // 
    double init_array[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    dtkDenseMatrix<double, 4, 4> m4(4, 4, init_array);

    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m4(i,j), m3(i,j));
        }
    }

    //
    dtkDenseMatrix<double, 4, 4> m5(m4);
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m4(i,j), m5(i,j));
        }
    }

    //
    dtkDenseMatrix<double> m6(m5);
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m6(i,j), m5(i,j));
        }
    }

    dtkDenseMatrixBase<dtkDenseMatrix<double>, false > *m7 = &m6;
    
    dtkDenseMatrix<double> m8(~(*m7));
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m8(i,j), m6(i,j));
        }
    }

    // Complex Values.
    ComplexValue::destroyCount = 0;
    {
        dtkDenseMatrix<ComplexValue> m9(4,4);
        for (qlonglong i = 0; i < 4; ++i) {
            for (qlonglong j =0; j < 4; ++j) {
                m9(i,j) = ComplexValue(i * m1.rowCount() + j);
            }
        }
        QCOMPARE(ComplexValue::destroyCount, 16); // Destruction of temporaries.
    }
    QCOMPARE(ComplexValue::destroyCount, 32);*/
}

void dtkMatrixTestCase::testAssign(void)
{
    dtkDenseMatrix<double> m0(4,4);
    m0.fill(1);
    flens::Range<qlonglong> row_range(1,3);
    flens::Range<qlonglong> col_range(2,4);
    dtkDenseMatrix<double>::View m_view=m0(row_range,col_range);
    std::cerr<<col_range<<row_range;
    m_view.fill(4);
    
    for(qlonglong i=1;i<5;i++)
    {
        for(qlonglong j=1;j<5;j++)
        {
            qDebug()<<m0(j,i)<<i<<j;
            /*if((i==1 || i==2) && (j==2 || j==3))
                QVERIFY(m0(i,j)==4);
            else
                QVERIFY(m0(i,j)==1);  */   
        }
    }

    //
    /*dtkDenseMatrix<double> m0;
    QVERIFY(m0.isEmpty() && m0.empty());
    double init_values[4][4] = { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15} };

    m0 = init_values;
    QVERIFY(!m0.isEmpty() && !m0.empty());
    QVERIFY(m0.rowCount() == 4LL);
    QVERIFY(m0.colCount() == 4LL);
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m0.at(i,j), init_values[i][j]);
        }
    }

    //
    dtkDenseMatrix<double> m1;
    m1 = m0;
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m1.at(i,j), init_values[i][j]);
        }
    }
    QVERIFY(m1.constData() == m0.constData());
    
    dtkDenseMatrix<double, 3, 3> m2;
    m2 = m1;
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m2.at(i,j), init_values[i][j]);
        }
    }*/
}
/*
void dtkMatrixTestCase::testClearAndReset(void)
{
    double init_values[4][4] = { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15} };
    dtkDenseMatrix<double> m0(init_values);

    QCOMPARE(m0.rowCount(), 4LL);
    QCOMPARE(m0.colCount(), 4LL);
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m0.at(i,j), init_values[i][j]);
        }
    }

    // Reset
    m0.reset();
    QCOMPARE(m0.rowCount(), 4LL);
    QCOMPARE(m0.colCount(), 4LL);
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m0.at(i,j), 0.);
        }
    }

    m0 = init_values;
    QCOMPARE(m0.rowCount(), 4LL);
    QCOMPARE(m0.colCount(), 4LL);
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m0.at(i,j), init_values[i][j]);
        }
    }

    // clear
    m0.clear();
    QCOMPARE(m0.rowCount(), 0LL);
    QCOMPARE(m0.colCount(), 0LL);

    // Complex Values.
    ComplexValue::destroyCount = 0;
    dtkDenseMatrix<ComplexValue> m1(4,4);
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            m1(i,j) = ComplexValue(i * m1.rowCount() + j);
        }
    }
    QCOMPARE(ComplexValue::destroyCount, 16);
    ComplexValue::destroyCount = 0;
    
    // Reset
    m1.reset();
    QCOMPARE(m1.rowCount(), 4LL);
    QCOMPARE(m1.colCount(), 4LL);
    QCOMPARE(ComplexValue::destroyCount, 16);
    ComplexValue value;
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            QCOMPARE(m1.at(i,j), value);
        }
    }
    for (qlonglong i = 0; i < 4; ++i) {
        for (qlonglong j =0; j < 4; ++j) {
            m1(i,j) = ComplexValue(i * m1.rowCount() + j);
        }
    }
    ComplexValue::destroyCount = 0;
    
    // clear
    m1.clear();
    QCOMPARE(m1.rowCount(), 0LL);
    QCOMPARE(m1.colCount(), 0LL);
    QCOMPARE(ComplexValue::destroyCount, 16);

}

void dtkMatrixTestCase::testResize(void)
{
    double init_values[4][4] = { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15} };
    dtkDenseMatrix<double> m0(init_values);

    QCOMPARE(m0.rowCount(), 4LL);
    QCOMPARE(m0.colCount(), 4LL);
    qlonglong capacity = m0.capacity();

    m0.resize(2, 2);
    QCOMPARE(m0.rowCount(), 2LL);
    QCOMPARE(m0.colCount(), 2LL);
    QVERIFY(m0.capacity() <= capacity);
    
    m0.resize(128,128);
    QCOMPARE(m0.rowCount(), 128LL);
    QCOMPARE(m0.colCount(), 128LL);
}

void dtkMatrixTestCase::testReserve(void)
{
    dtkDenseMatrix<double> m0;
    m0.reserve(32);
    QCOMPARE(m0.capacity(), 32LL);
    qlonglong capacity = m0.capacity();

    double init_values[4][4] = { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15} };
    m0 = init_values;
    QCOMPARE(m0.rowCount(), 4LL);
    QCOMPARE(m0.colCount(), 4LL);
    QVERIFY(m0.capacity() <= capacity);
}

void dtkMatrixTestCase::testFill(void)
{
    double value = qSqrt(2);
    dtkDenseMatrix<double> m0(4,4);
    m0.fill(value);
    for (qlonglong i = 0; i < 16; ++i) {
        QCOMPARE(m0.constData()[i], value);
    }
}

void dtkMatrixTestCase::testIterator(void)
{
    double init_values[4][5] = { {0, 1, 2, 3, 4}, {5, 6, 7, 8, 9}, {10, 11, 12, 13, 14}, {15, 16, 17, 18, 19} };
    dtkDenseMatrix<double> m0(init_values);

    for (qlonglong i = 0; i < 4; ++i) {
        dtkDenseMatrix<double>::const_iterator cit = m0.cbegin(i);
        dtkDenseMatrix<double>::const_iterator cend = m0.cend(i);
        for (qlonglong j = 0; cit != cend; ++cit, ++j) {
            QCOMPARE((*cit), init_values[i][j]);
            QPair<qlonglong, qlonglong> coords = m0.coordinatesOf(cit);
            QCOMPARE(i, coords.first);
            QCOMPARE(j, coords.second);
        }
    }

    dtkDenseMatrix<double>::iterator it  = m0.begin();
    dtkDenseMatrix<double>::iterator end = m0.end();
    for (qlonglong count = 0; it != end; ++it, ++count) {
        *it += 1;
        QPair<qlonglong, qlonglong> coords = m0.coordinatesOf(it);
        qlonglong j = count % 5LL;
        qlonglong i = (count - j) / 5LL;
        QCOMPARE(i, coords.first);
        QCOMPARE(j, coords.second);
    }

    for (qlonglong i = 0; i < 4; ++i) {
        dtkDenseMatrix<double>::const_iterator cit = m0.cbegin(i);
        dtkDenseMatrix<double>::const_iterator cend = m0.cend(i);
        for (qlonglong j = 0; cit != cend; ++cit, ++j) {
            QCOMPARE((*cit) - 1, init_values[i][j]);
        }
    }

    
}*/

void dtkMatrixTestCase::cleanupTestCase(void)
{

}

void dtkMatrixTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkMatrixTest, dtkMatrixTestCase)

// 
// dtkMatrixTest.cpp ends here
