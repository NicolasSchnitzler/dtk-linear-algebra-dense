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
    dtkDenseVector& operator = (const T& value);

public:
    template <typename RHS> dtkDenseVector& operator  = (const flens::Vector<RHS>& rhs);

    template <typename RHS> dtkDenseVector& operator += (const flens::Vector<RHS>& rhs);
    template <typename RHS> dtkDenseVector& operator -= (const flens::Vector<RHS>& rhs);

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
    void resize(qlonglong) {;}
    void append(std::initializer_list<T>) {;}
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
    T  last(void) const { return dtkDenseVector<T>::last(); }

public:
    const T& operator [] (qlonglong index) const { return dtkDenseVector<T>::operator[](index); }

public:
    const T& operator () (qlonglong index) const { return dtkDenseVector<T>::operator()(index); }

public:
    const T *data(void) const { return dtkDenseVector<T>::data(); }

    const T *constData(void) const { return dtkDenseVector<T>::constData(); }

public:
    const dtkDenseVector<T>::ConstView operator() (const Range& range) const { return dtkDenseVector<T>::operator() (range); }
    const dtkDenseVector<T>::ConstView operator() (const Range& range, qlonglong first_index) const { return dtkDenseVector<T>::operator() (range, first_index); }
    const ConstView operator() (const Underscore& all, qlonglong first_index) const { return dtkDenseVector<T>::operator() (all, first_index); }
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDenseVector.tpp"

//
// dtkDenseVector.h ends here
