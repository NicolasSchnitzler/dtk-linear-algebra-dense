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

template < typename T > class dtkDenseMatrix;

namespace flens {

template < typename T > class Matrix< GeneralMatrix<dtkDenseMatrix<T> > >
{
public:
    typedef GeMatrix< FullStorageView<T,flens::ColMajor> > Impl;

    virtual ~Matrix(void) {}

    const Impl& impl(void) const;
          Impl& impl(void);
};

}

template <typename T> using dtkMatrixBase = flens::Matrix< flens::GeneralMatrix<dtkDenseMatrix<T> > >;

// ///////////////////////////////////////////////////////////////////
// dtkDenseMatrix declaration
// ///////////////////////////////////////////////////////////////////

template < typename T > class dtkDenseMatrix : public dtkMatrixBase<T>
{
    
private:
    typedef typename flens::GeMatrix< flens::FullStorageView<T,flens::ColMajor> > FlensView;
    typedef typename FlensView::Engine                                            Engine;

private:
    FlensView *m_view;
    Engine *m_engine;
    dtkArray<T> m_array;
    
private:
    const FlensView& impl(void) const;
          FlensView& impl(void);
          
public:
    typedef flens::Range<qlonglong> Range;
    typedef flens::Underscore<qlonglong> Underscore;

public:
    dtkDenseMatrix(void);
    dtkDenseMatrix(qlonglong row_count, qlonglong col_count);
    dtkDenseMatrix(const dtkDenseMatrix &rhs);
    
protected:
    dtkDenseMatrix(const T *data, qlonglong row_count, qlonglong col_count, qlonglong first_row, qlonglong first_col);
    dtkDenseMatrix(      T *data, qlonglong row_count, qlonglong col_count, qlonglong first_row, qlonglong first_col);

public:
    virtual ~dtkDenseMatrix();

public:
    bool      isEmpty (void) const;
    qlonglong rowCount(void) const;  
    qlonglong colCount(void) const;
    
public:
    qlonglong firstRow(void) const;
    qlonglong firstCol(void) const;

public:
    void fill(T value);
    
public:
    const T& operator () (qlonglong row, qlonglong col) const;
    T& operator () (qlonglong row, qlonglong col);

public:
    const T *data(void) const;
          T *data(void);

    const T *constData(void) const;
    
public:
    class View;
    class ConstView;
    
public:
    const ConstView operator() (const Range& row_range, const Range& col_range) const;
               View operator() (const Range& row_range, const Range& col_range);

    const ConstView operator() (const Range& row_range, const Range& col_range, qlonglong first_row, qlonglong first_col) const;
               View operator() (const Range& row_range, const Range& col_range, qlonglong first_row, qlonglong first_col);

    /*const ConstView operator() (const Underscore& all, qlonglong first_index) const;
               View operator() (const Underscore& all, qlonglong first_index);*/
    
};


// ///////////////////////////////////////////////////////////////////
// dtkDenseMatrix::View declaration
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkDenseMatrix<T>::View : public dtkDenseMatrix<T>
{
public:
    View(T *data,  qlonglong row_count, qlonglong col_count, qlonglong first_row, qlonglong first_col);
    View(const View& rhs);
};

// ///////////////////////////////////////////////////////////////////
// dtkDenseMatrix::ConstView declaration
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkDenseMatrix<T>::ConstView : private dtkDenseMatrix<T>
{
public:
    ConstView(T *data, qlonglong row_count, qlonglong col_count, qlonglong first_row, qlonglong first_col);
    ConstView(const ConstView& rhs);
    ConstView(const View& rhs);

public:
    bool isEmpty(void) const { return dtkDenseMatrix<T>::isEmpty(); }

    qlonglong   size(void) const { return dtkDenseMatrix<T>::size(); }
    qlonglong length(void) const { return dtkDenseMatrix<T>::size(); }

    qlonglong stride(void) const { return dtkDenseMatrix<T>::stride(); }

public:
    T at(const qlonglong& index) const { return dtkDenseMatrix<T>::at(index); }

    T first(void) const { return dtkDenseMatrix<T>::first(); }
    T  last(void) const { return dtkDenseMatrix<T>::last(); }

public:
    const T& operator [] (qlonglong index) const { return dtkDenseMatrix<T>::operator[](index); }

public:
    const T& operator () (qlonglong index) const { return dtkDenseMatrix<T>::operator()(index); }

public:
    const T *data(void) const { return dtkDenseMatrix<T>::data(); }

    const T *constData(void) const { return dtkDenseMatrix<T>::constData(); }

public:
    const dtkDenseMatrix<T>::ConstView operator() (const Range& range) const { return dtkDenseMatrix<T>::operator() (range); }
    const dtkDenseMatrix<T>::ConstView operator() (const Range& range, qlonglong first_index) const { return dtkDenseMatrix<T>::operator() (range, first_index); }
    const ConstView operator() (const Underscore& all, qlonglong first_index) const { return dtkDenseMatrix<T>::operator() (all, first_index); }
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDenseMatrix.tpp"

// 
// dtkDenseMatrix.h ends here
