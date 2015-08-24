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

#pragma once

#include "dtkLinearAlgebraDense.h"

#include <flens/flens.cxx>

#include <dtkCore>
#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// CRTP base class declaraton
// ///////////////////////////////////////////////////////////////////

template < typename T > class dtkDenseVector;

namespace flens {

template < typename T > class Vector< dtkDenseVector<T> >
{
public:
    typedef DenseVector< ArrayView<T> > Impl;

    virtual ~Vector(void) {}

    const Impl& impl(void) const;
          Impl& impl(void);
};

}

// ///////////////////////////////////////////////////////////////////
// dtkDenseVector declaration
// ///////////////////////////////////////////////////////////////////

template < typename T > class dtkDenseVector : public flens::Vector< dtkDenseVector<T> >
{
private:
    typedef typename flens::DenseVector< flens::ArrayView<T> > FlensView;
    typedef typename FlensView::Engine                         Engine;

private:
    FlensView *m_view;
    Engine *m_engine;
    dtkArray<T> m_array;

private:
    friend class flens::Vector< dtkDenseVector<T> >;
    const FlensView& impl(void) const;
          FlensView& impl(void);

public:
    typedef flens::Range<qlonglong> Range;
    typedef flens::Underscore<qlonglong> Underscore;

public:
    dtkDenseVector(void);
    dtkDenseVector(qlonglong size);
    dtkDenseVector(std::initializer_list<T> list);
    dtkDenseVector(const dtkDenseVector<T>& rhs);

public:
    template <typename RHS> dtkDenseVector(const flens::Vector<RHS>& rhs);

protected:
    dtkDenseVector(const T *data, qlonglong size, qlonglong stride, qlonglong first_index);
    dtkDenseVector(      T *data, qlonglong size, qlonglong stride, qlonglong first_index);

public:
    virtual ~dtkDenseVector(void);

public:
    template <typename RHS> dtkDenseVector& operator  = (const flens::Vector<RHS>& rhs);

    template <typename RHS> dtkDenseVector& operator += (const flens::Vector<RHS>& rhs);
    template <typename RHS> dtkDenseVector& operator -= (const flens::Vector<RHS>& rhs);

public:
    dtkDenseVector& operator = (const T& value);

public:
    template <typename S> typename std::enable_if<std::is_convertible<S, T>::value, dtkDenseVector>::type& operator *= (const S& alpha);
    template <typename S> typename std::enable_if<std::is_convertible<S, T>::value, dtkDenseVector>::type& operator /= (const S& alpha);

public:
    bool empty(void) const;

    qlonglong   size(void) const;
    qlonglong length(void) const;

    qlonglong stride(void) const;

public:
    qlonglong firstIndex(void) const;
    qlonglong  lastIndex(void) const;

public:
    void clear(void);

    void resize(const qlonglong& size);

    void append(std::initializer_list<T> list);

public:
    void fill(const T& value);

public:
    void setAt(const qlonglong& index, const T& value);

    const T& at(const qlonglong& index) const;

    const T& first(void) const;
    const T&  last(void) const;

public:
    const T& operator [] (qlonglong index) const;
          T& operator [] (qlonglong index);

public:
    const T& operator () (qlonglong index) const;
          T& operator () (qlonglong index);

public:
    const T *data(void) const;
          T *data(void);

    const T *constData(void) const;

public:
    class View;
    class ConstView;

public:
    const ConstView operator() (const Range& range) const;
               View operator() (const Range& range);

    const ConstView operator() (const Range& range, qlonglong first_index) const;
               View operator() (const Range& range, qlonglong first_index);

    const ConstView operator() (const Underscore& all, qlonglong first_index) const;
               View operator() (const Underscore& all, qlonglong first_index);

public:
    class iterator {
    public:
        T *i;
        qlonglong inc;
        typedef std::random_access_iterator_tag iterator_category;
        typedef qintptr difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;

    public:
        iterator(void) : i(0), inc(1LL) {}
        iterator(T *n, qlonglong increment) : i(n), inc(increment) {}

    public:
        T& operator *  (void) const { return *i; }
        T *operator -> (void) const { return  i; }
        T& operator [] (qintptr j) const { return *(i + j); }
        bool operator == (const iterator &o) const { return i == o.i; }
        bool operator != (const iterator &o) const { return i != o.i; }
        bool operator <  (const iterator& other) const { return i <  other.i; }
        bool operator <= (const iterator& other) const { return i <= other.i; }
        bool operator >  (const iterator& other) const { return i >  other.i; }
        bool operator >= (const iterator& other) const { return i >= other.i; }
        iterator& operator ++ (void) { i += inc; return *this; }
        iterator  operator ++ (int) { T *n = i; i += inc; return n; }
        iterator& operator -- (void) { i -= inc; return *this; }
        iterator  operator -- (int) { T *n = i; i -= inc; return n; }
        iterator& operator += (qintptr j) { i+=j*inc; return *this; }
        iterator& operator -= (qintptr j) { i-=j*inc; return *this; }
        iterator  operator +  (qintptr j) const { return iterator(i+j*inc, inc); }
        iterator  operator -  (qintptr j) const { return iterator(i-j*inc, inc); }
        qintptr operator - (const iterator& j) const { return (i - j.i) / inc; }
        operator T* (void) const { return i; }
    };
    friend class iterator;

public:
    class const_iterator {
    public:
        const T *i;
        qlonglong inc;
        typedef std::random_access_iterator_tag  iterator_category;
        typedef qintptr difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;

    public:
                 const_iterator(void) : i(0), inc(1LL) {}
                 const_iterator(const T *n, qlonglong increment) : i(n), inc(increment) {}
        explicit const_iterator(const iterator &o): i(o.i), inc(o.inc) {}

    public:
        const T& operator *  (void) const { return *i; }
        const T *operator -> (void) const { return  i; }
        const T& operator [] (qintptr j) const { return *(i + j); }
        bool operator == (const const_iterator &o) const { return i == o.i; }
        bool operator != (const const_iterator &o) const { return i != o.i; }
        bool operator <  (const const_iterator& other) const { return i <  other.i; }
        bool operator <= (const const_iterator& other) const { return i <= other.i; }
        bool operator >  (const const_iterator& other) const { return i >  other.i; }
        bool operator >= (const const_iterator& other) const { return i >= other.i; }
        const_iterator &operator ++ (void) { i += inc; return *this; }
        const_iterator operator  ++ (int) { const T *n = i; i += inc; return n; }
        const_iterator &operator -- (void) { i -= inc; return *this; }
        const_iterator operator  -- (int) { const T *n = i; i -= inc; return n; }
        const_iterator &operator += (qintptr j) { i+=j*inc; return *this; }
        const_iterator &operator -= (qintptr j) { i-=j*inc; return *this; }
        const_iterator operator  +  (qintptr j) const { return const_iterator(i+j*inc, inc); }
        const_iterator operator  -  (qintptr j) const { return const_iterator(i-j*inc, inc); }
        qintptr operator - (const const_iterator& j) const { return (i - j.i) / inc; }
        operator const T* (void) const { return i; }
    };
    friend class const_iterator;

public:
    typedef iterator            Iterator;
    typedef const_iterator ConstIterator;

public:
          iterator begin(void)            { return       iterator(data(), stride()); }
    const_iterator begin(void)      const { return const_iterator(data(), stride()); }
    const_iterator cbegin(void)     const { return const_iterator(data(), stride()); }
    const_iterator constBegin(void) const { return const_iterator(data(), stride()); }

          iterator end(void)            { return       iterator(data() + size(), stride()); }
    const_iterator end(void)      const { return const_iterator(data() + size(), stride()); }
    const_iterator cend(void)     const { return const_iterator(data() + size(), stride()); }
    const_iterator constEnd(void) const { return const_iterator(data() + size(), stride()); }
};

// ///////////////////////////////////////////////////////////////////
// dtkDenseVector::View declaration
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkDenseVector<T>::View : public dtkDenseVector<T>
{
public:
    View(T *data, qlonglong size, qlonglong stride, qlonglong first_index);
    View(const View& rhs);

private:
    void clear(void) {;}
    void resize(qlonglong) {;}
    void append(std::initializer_list<T>) {;}

private:
    friend class dtkDenseVector;
};

// ///////////////////////////////////////////////////////////////////
// dtkDenseVector::ConstView declaration
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkDenseVector<T>::ConstView : private dtkDenseVector<T>
{
public:
    ConstView(const T *data, qlonglong size, qlonglong stride, qlonglong first_index);
    ConstView(const ConstView& rhs);
    ConstView(const View& rhs);

public:
    bool empty(void) const { return dtkDenseVector<T>::empty(); }

    qlonglong   size(void) const { return dtkDenseVector<T>::size(); }
    qlonglong length(void) const { return dtkDenseVector<T>::size(); }

    qlonglong stride(void) const { return dtkDenseVector<T>::stride(); }

public:
    T at(const qlonglong& index) const { return dtkDenseVector<T>::at(index); }

    T first(void) const { return dtkDenseVector<T>::first(); }
    T  last(void) const { return dtkDenseVector<T>::last();  }

public:
    qlonglong firstIndex(void) const { return dtkDenseVector<T>::firstIndex(); }
    qlonglong  lastIndex(void) const { return dtkDenseVector<T>::lastIndex();  }

public:
    const T& operator [] (qlonglong index) const { return dtkDenseVector<T>::operator[](index); }

public:
    const T& operator () (qlonglong index) const { return dtkDenseVector<T>::operator()(index); }

public:
    const T *data(void) const { return dtkDenseVector<T>::data(); }

    const T *constData(void) const { return dtkDenseVector<T>::constData(); }

public:
    const ConstView operator() (const Range& range) const { return dtkDenseVector<T>::operator() (range); }
    const ConstView operator() (const Range& range, qlonglong first_index) const { return dtkDenseVector<T>::operator() (range, first_index); }
    const ConstView operator() (const Underscore& all, qlonglong first_index) const { return dtkDenseVector<T>::operator() (all, first_index); }

public:
    const_iterator begin(void)      const { return dtkDenseVector<T>::cbegin(); }
    const_iterator cbegin(void)     const { return dtkDenseVector<T>::cbegin(); }
    const_iterator constBegin(void) const { return dtkDenseVector<T>::cbegin(); }

    const_iterator end(void)      const { return dtkDenseVector<T>::cend(); }
    const_iterator cend(void)     const { return dtkDenseVector<T>::cend(); }
    const_iterator constEnd(void) const { return dtkDenseVector<T>::cend(); }
};

// ///////////////////////////////////////////////////////////////////
// Helpers
// ///////////////////////////////////////////////////////////////////

template < typename T > QDebug& operator << (QDebug debug, const dtkDenseVector<T>& vec);

template < typename T > QDataStream& operator << (QDataStream& s, const dtkDenseVector<T>& vec);
template < typename T > QDataStream& operator >> (QDataStream& s,       dtkDenseVector<T>& vec);

// ///////////////////////////////////////////////////////////////////

#include "dtkDenseVector.tpp"

//
// dtkDenseVector.h ends here
