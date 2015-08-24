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
    {
        dtkDenseVector<double> v;
        QVERIFY(v.empty());
        QVERIFY(!v.size());
        QVERIFY(!v.length());
    }

    {
        dtkDenseVector<double> v(101);
        QVERIFY(!v.empty());
        QCOMPARE(v.size(), 101LL);
        QCOMPARE(v.length(), 101LL);
        QCOMPARE(v.stride(), 1LL);
        QCOMPARE(v.firstIndex(), 1LL);
        QCOMPARE(v.lastIndex(), 101LL);
    }

    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        QVERIFY(!v.empty());
        QCOMPARE(v.size(), 7LL);
        QCOMPARE(v.length(), 7LL);
        QCOMPARE(v.stride(), 1LL);
        QCOMPARE(v.firstIndex(), 1LL);
        QCOMPARE(v.lastIndex(), 7LL);

        dtkDenseVector<double> v_copy(v);
        QVERIFY(!v_copy.empty());
        QCOMPARE(v_copy.size(), 7LL);
        QCOMPARE(v_copy.length(), 7LL);
        QCOMPARE(v_copy.stride(), 1LL);
        QCOMPARE(v_copy.firstIndex(), 1LL);
        QCOMPARE(v_copy.lastIndex(), 7LL);
    }

    {
        flens::DenseVector< flens::Array<double> > fv(11);
        fv = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11;

        dtkDenseVector<double> v(fv);
        QVERIFY(!v.empty());
        QCOMPARE(v.size(), 11LL);
        QCOMPARE(v.length(), 11LL);
        QCOMPARE(v.stride(), 1LL);
        QCOMPARE(v.firstIndex(), 1LL);
        QCOMPARE(v.lastIndex(), 11LL);
    }
}

void dtkDenseVectorTestCase::testClear(void)
{
    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        v.clear();
        QVERIFY(v.empty());
        QVERIFY(!v.size());
        QVERIFY(!v.length());
    }
}

void dtkDenseVectorTestCase::testGetValue(void)
{
    {
        std::initializer_list<double> list = {1, 2, 3, 4, 5, 6, 7};
        auto it = list.begin();
        dtkDenseVector<double> v(list);

        QCOMPARE(v.first(), *it);

        for(qlonglong i = 1; i <= v.size(); ++i, ++it) {
            QCOMPARE(v(i), *it);
            QCOMPARE(v[i], *it);
            QCOMPARE(v.at(i), *it);
        }

        QCOMPARE(v.last(), *(--it));
    }

    {
        std::initializer_list<double> list = {1, 2, 3, 4, 5, 6, 7};
        auto it = list.begin();
        const dtkDenseVector<double> v(list);

        QCOMPARE(v.first(), *it);

        for(qlonglong i = 1; i <= v.size(); ++i, ++it) {
            QCOMPARE(v(i), *it);
            QCOMPARE(v[i], *it);
            QCOMPARE(v.at(i), *it);
        }

        QCOMPARE(v.last(), *(--it));
    }
}

void dtkDenseVectorTestCase::testSetValue(void)
{
    {
        std::initializer_list<double> list = {1, 2, 3, 4, 5, 6, 7};
        auto it = list.begin();
        dtkDenseVector<double> v(7);

        for(qlonglong i = 1; i <= v.size(); ++i, ++it) {
            v.setAt(i, *it);
            QCOMPARE(v.at(i), *it);
        }
    }

    {
        std::initializer_list<double> list = {1, 2, 3, 4, 5, 6, 7};
        auto it = list.begin();
        dtkDenseVector<double> v(7);

        for(qlonglong i = 1; i <= v.size(); ++i, ++it) {
            v(i) = *it;
            QCOMPARE(v(i), *it);
        }
    }

    {
        std::initializer_list<double> list = {1, 2, 3, 4, 5, 6, 7};
        auto it = list.begin();
        dtkDenseVector<double> v(7);

        for(qlonglong i = 1; i <= v.size(); ++i, ++it) {
            v[i] = *it;
            QCOMPARE(v[i], *it);
        }
    }
}

void dtkDenseVectorTestCase::testResize(void)
{
    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        dtkDenseVector<double> w(v);
        w.resize(11);
        QCOMPARE(w.size(), 11LL);
        QCOMPARE(w.length(), 11LL);
        QCOMPARE(w.stride(), 1LL);
        QCOMPARE(w.firstIndex(), 1LL);
        QCOMPARE(w.lastIndex(), 11LL);

        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(w(i), v(i));
        }
    }
}

void dtkDenseVectorTestCase::testFill(void)
{
    {
        double pi = 3.14159;
        dtkDenseVector<double> v(101);
        v.fill(pi);
        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), pi);
        }
    }
}

void dtkDenseVectorTestCase::testAppend(void)
{
    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        v.append({8, 9, 10, 11});

        QCOMPARE(v.size(), 11LL);
        QCOMPARE(v.length(), 11LL);
        QCOMPARE(v.stride(), 1LL);
        QCOMPARE(v.firstIndex(), 1LL);
        QCOMPARE(v.lastIndex(), 11LL);

        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), i * 1.);
        }

    }
}

void dtkDenseVectorTestCase::testAssign(void)
{
    {
        flens::DenseVector< flens::Array<double> > fv(11);
        fv = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11;

        dtkDenseVector<double> v; v = fv;
        QVERIFY(!v.empty());
        QCOMPARE(v.size(), 11LL);
        QCOMPARE(v.length(), 11LL);
        QCOMPARE(v.stride(), 1LL);
        QCOMPARE(v.firstIndex(), 1LL);
        QCOMPARE(v.lastIndex(), 11LL);
    }
}

void dtkDenseVectorTestCase::testAddAssign(void)
{
    {
        flens::DenseVector< flens::Array<double> > fv(11);
        fv = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11;

        dtkDenseVector<double> v(11);
        double pi = 3.14159;
        v.fill(pi);
        v += fv;

        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), pi + fv(i));
        }
    }

    {
        dtkDenseVector<double> fv = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

        dtkDenseVector<double> v(11);
        double pi = 3.14159;
        v.fill(pi);
        v += fv;

        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), pi + fv(i));
        }
    }
}

void dtkDenseVectorTestCase::testSubAssign(void)
{
    {
        flens::DenseVector< flens::Array<double> > fv(11);
        fv = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11;

        dtkDenseVector<double> v(11);
        double pi = 3.14159;
        v.fill(pi);
        v -= fv;

        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), pi - fv(i));
        }
    }
}

void dtkDenseVectorTestCase::testAssignValue(void)
{
    {
        double pi = 3.14159;
        dtkDenseVector<double> v(101);
        v = pi;
        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), pi);
        }
    }
}

void dtkDenseVectorTestCase::testScal(void)
{
    {
        double pi = 3.14159;
        dtkDenseVector<double> v(101);
        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            v(i) = i;
        }

        v *= pi;

        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), pi * i);
        }
    }

    {
        double pi = 3.14159;
        dtkDenseVector<double> v(101);
        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            v(i) = i;
        }

        v /= pi;

        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), i / pi);
        }
    }
}

void dtkDenseVectorTestCase::testIterator(void)
{
    {
        std::initializer_list<double> list = {1, 2, 3, 4, 5, 6, 7};
        auto it = list.begin();
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        for(const double& val : v) {
            QCOMPARE(val, *it);
            ++it;
        }
    }

    {
        std::initializer_list<double> list = {1, 2, 3, 4, 5, 6, 7};
        auto it = list.begin();
        dtkDenseVector<double> v(7);
        qlonglong i = 1;
        for(double& val : v) {
            val = *it;
            QCOMPARE(v(i), *it);
            ++it; ++i;
        }
    }
}

void dtkDenseVectorTestCase::testData(void)
{
    {
        const dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        const double *buf = v.data();

        QVERIFY(buf);
        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), *(buf + i - 1));
        }
    }
    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        double *buf = v.data();

        QVERIFY(buf);
        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), *(buf + i - 1));
        }

        const double *c_buf = v.constData();

        QVERIFY(c_buf);
        for(qlonglong i = v.firstIndex(); i <= v.lastIndex(); ++i) {
            QCOMPARE(v(i), *(c_buf + i - 1));
        }
    }
}

void dtkDenseVectorTestCase::testView(void)
{
    dtkDenseVector<double>::Underscore _;
    typedef typename dtkDenseVector<double>::View View;

    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        View view = v(_(3, 6));

        QVERIFY(!view.empty());
        QCOMPARE(view.size(), 4LL);
        QCOMPARE(view.length(), 4LL);
        QCOMPARE(view.stride(), 1LL);
        QCOMPARE(view.firstIndex(), 1LL);
        QCOMPARE(view.lastIndex(), 4LL);

        for(qlonglong i = view.firstIndex(); i <= view.lastIndex(); ++i) {
            QCOMPARE(view(i), v(i + 2));
        }

        double pi = 3.14159;
        for(qlonglong i = view.firstIndex(); i <= view.lastIndex(); ++i) {
            view(i) = pi + i;
        }

        for(qlonglong i = view.firstIndex(); i <= view.lastIndex(); ++i) {
            QCOMPARE(v(i + 2), pi + i);
        }
    }

    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        View view = v(_(3, 2, 6));

        QVERIFY(!view.empty());
        QCOMPARE(view.size(), 2LL);
        QCOMPARE(view.length(), 2LL);
        QCOMPARE(view.stride(), 2LL);
        QCOMPARE(view.firstIndex(), 1LL);
        QCOMPARE(view.lastIndex(), 2LL);

        for(qlonglong i = view.firstIndex(); i <= view.lastIndex(); ++i) {
            QCOMPARE(view(i), v(3 + 2 * (i-1)));
        }

        dtkDenseVector<double> ref = v;
        dtkDenseVector<double> w = {3.14159, 0.33333};
        view += w;

        auto it = view.begin();
        for(qlonglong i = view.firstIndex(); i <= view.lastIndex(); ++i, ++it) {
            QCOMPARE(view(i), ref(3 + 2 * (i-1)) + w(i));
            QCOMPARE(*it, ref(3 + 2 * (i-1)) + w(i));
        }
    }

    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        View view = v(_(1, 2, 7));

        View view2 = view(_(view.firstIndex(), 2, view.lastIndex()));

        QVERIFY(!view2.empty());
        QCOMPARE(view2.size(), 2LL);
        QCOMPARE(view2.length(), 2LL);
        QCOMPARE(view2.stride(), 4LL);
        QCOMPARE(view2.firstIndex(), 1LL);
        QCOMPARE(view2.lastIndex(), 2LL);

        auto it = view2.begin();
        for(qlonglong i = view2.firstIndex(); i <= view2.lastIndex(); ++i, ++it) {
            QCOMPARE(view2(i), v(1 + 4 * (i-1)));
            QCOMPARE(*it, v(1 + 4 * (i-1)));
        }
    }
}

void dtkDenseVectorTestCase::testConstView(void)
{
    dtkDenseVector<double>::Underscore _;
    typedef typename dtkDenseVector<double>::View           View;
    typedef typename dtkDenseVector<double>::ConstView ConstView;

    {
        const dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        ConstView cview = v(_(3, 6));

        QVERIFY(!cview.empty());
        QCOMPARE(cview.size(), 4LL);
        QCOMPARE(cview.length(), 4LL);
        QCOMPARE(cview.stride(), 1LL);
        QCOMPARE(cview.firstIndex(), 1LL);
        QCOMPARE(cview.lastIndex(), 4LL);

        for(qlonglong i = cview.firstIndex(); i <= cview.lastIndex(); ++i) {
            QCOMPARE(cview(i), v(i + 2));
        }
    }

    {
        dtkDenseVector<double> v({1, 2, 3, 4, 5, 6, 7});
        ConstView cview = v(_(3, 6));

        QVERIFY(!cview.empty());
        QCOMPARE(cview.size(), 4LL);
        QCOMPARE(cview.length(), 4LL);
        QCOMPARE(cview.stride(), 1LL);
        QCOMPARE(cview.firstIndex(), 1LL);
        QCOMPARE(cview.lastIndex(), 4LL);

        auto it = cview.begin();
        for(qlonglong i = cview.firstIndex(); i <= cview.lastIndex(); ++i, ++it) {
            QCOMPARE(cview(i), v(i + 2));
            QCOMPARE(*it, v(i + 2));
        }
    }
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
