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

#include "dtkDenseVectorTest.h"

#include <dtkLinearAlgebraDense>

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

void dtkDenseVectorTestCase::initTestCase(void)
{

}

void dtkDenseVectorTestCase::init(void)
{

}

void dtkDenseVectorTestCase::testCreate(void)
{
    // // Check the basic properties.
    // dtkDenseVector<double> v0(11);

    // for (int i = 1; i < 12; ++i) {
    //     v0(i) = i;
    // }
    // for (int i = 1; i < 12; ++i) {
    //     qDebug() << i << v0(i);
    // }
    

    // dtkDenseVector<double> v1(11);

    // flens::fillRandom(v1);
    // for (int i = 1; i < 12; ++i) {
    //     qDebug() << i << v1(i);
    // }

    // v1 = v0;

    // dtkDenseVector<double> v2;

    // double scal = v0 * v1;

    // qDebug() << qSqrt(scal);

    // scal = dtk::blas::normL2(v1);
    // qDebug() << scal;


    // double sum = dtk::blas::asum(v1);
    // double sum_check = 0;
    // for (int i = 1; i < 12; ++i) {
    //     sum_check += v1(i);
    // }

    // qDebug() << sum << sum_check;

    // dtk::blas::asum(v1, sum_check);
    
    // qDebug() << sum << sum_check;

    // //dtk::blas::axpy(sum, v0, v1);

    // v1 += sum * v0;

    // dtk::blas::copy(v0, v1);

    // std::cout << v1 << std::endl;

    // scal = dtk::blas::dot(v0, v1);

    // sum = dtk::blas::dotu(v0, v1);
    
    // qDebug() << sum << scal;

    // dtk::blas::scal(3.1416, v0);

    // std::cout << v0 << std::endl;

    // dtk::blas::swap(v0, v1);

    // std::cout << v0 << std::endl;
    // std::cout << v1 << std::endl;
}

void dtkDenseVectorTestCase::testAssign(void)
{
    dtkDenseVector<double>::Underscore _;
    dtkDenseVector<double> v(11);
    
    flens::DenseVector<flens::Array<double> > fv(11);

    for (int i = 1; i < 12; ++i) {
        fv(i) = i;
        qDebug() << i << fv(i);
    }
    
    v = fv;
    for (int i = 1; i < 12; ++i) {
        qDebug() << v(i);
    }

    dtkDenseVector<double> vv(11);

    vv = 1.5 * v + fv;

    for (int i = 1; i < 12; ++i) {
        qDebug() << vv(i) << 2.5 * v(i);
    }

    dtkDenseVector<double> vv2(11);
    
    vv2 = 1.5 * vv + fv + v;

    for (int i = 1; i < 12; ++i) {
        qDebug() << vv2(i);
    }

    double scal = vv2 * vv;

    qDebug() << scal;

    //fv = vv2;

    vv2.resize(10);

    qDebug() << vv2.size();

    flens::DenseVector<flens::ArrayView<double> > view(fv);

    //dtkDenseVector<double> v_noview(fv);
    //dtkDenseVector<double> v_view(view); 

    //std::cout << v_noview.impl() << std::endl;

    dtkDenseVector<double>::View v_view = v(_(1, 2, 11));

    qDebug() << v_view.data() << v.data();

    // std::cout << v_view.impl() << std::endl;

    v_view(1) += 1;

    qDebug() << v_view.data() << v.data();

    // std::cout << v_view.impl() << std::endl;
    // std::cout << v.impl() << std::endl;

    dtkDenseVector<double>::ConstView vv_view = v_view(_, 1);
    // std::cout << v_view.impl() << std::endl;
    // std::cout << vv_view.impl() << std::endl;
    qDebug() << vv_view.stride();

    dtkDenseVector<double> w = {1., 2., 3., 4., 5.};
    // std::cout << w.impl() << std::endl;

    w.append({ 1., 2., 3., 4., 5. });
    qDebug() << w.size();
    // std::cout << w.impl() << std::endl;
}

void dtkDenseVectorTestCase::testClearAndReset(void)
{

}

void dtkDenseVectorTestCase::testResize(void)
{
}

void dtkDenseVectorTestCase::testReserve(void)
{
}

void dtkDenseVectorTestCase::testFill(void)
{
}

void dtkDenseVectorTestCase::testIterator(void)
{

    
}

void dtkDenseVectorTestCase::cleanupTestCase(void)
{

}

void dtkDenseVectorTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDenseVectorTest, dtkDenseVectorTestCase)

// 
// dtkDenseVectorTest.cpp ends here
