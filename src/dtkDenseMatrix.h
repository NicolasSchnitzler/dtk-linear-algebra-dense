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

#include <QtCore>



template < typename T > class dtkDenseMatrix : public flens::GeneralMatrix< dtkDenseMatrix<T> >
{
    flens::GeMatrix< flens::FullStorage<T> > mat;    

public:
    typedef typename flens::GeMatrix< flens::FullStorage<T> >::Engine Engine;
    typedef typename Engine::ElementType                              ElementType;
    typedef typename Engine::IndexType                                IndexType;

    // view types from Engine
    typedef typename Engine::ConstView              EngineConstView;
    typedef typename Engine::View                   EngineView;
    typedef typename Engine::NoView                 EngineNoView;

    typedef typename Engine::ConstArrayView         ConstArrayView;
    typedef typename Engine::ArrayView              ArrayView;
    typedef typename Engine::Array                  Array;

    // view types
    typedef flens::DenseVector<ConstArrayView>             ConstVectorView;
    typedef flens::DenseVector<ArrayView>                  VectorView;
    typedef flens::DenseVector<Array>                      Vector;

    typedef dtkDenseMatrix<EngineConstView>               ConstView;
    typedef dtkDenseMatrix<EngineView>                    View;
    typedef dtkDenseMatrix<EngineNoView>                  NoView;

private:
    typedef dtkDenseMatrix                          DM;

public:
    typedef flens::IndexVariable<IndexType>                IndexVariable;
    typedef flens::gematrix::ConstElementClosure<DM>       ConstElementClosure;
    typedef flens::gematrix::ElementClosure<DM>            ElementClosure;
    typedef flens::gematrix::Initializer<DM>               Initializer;


public:
    dtkDenseMatrix(void) {}
    dtkDenseMatrix(IndexType numRows, IndexType numCols) : mat(numRows, numCols) {}
    dtkDenseMatrix(IndexType numRows, IndexType numCols, IndexType firstRow, IndexType firstCol) : mat(numRows, numCols, firstRow, firstCol) {}
    dtkDenseMatrix(const dtkDenseMatrix &rhs) : mat(rhs.mat) {}

public:
    qlonglong rowCount(void) const { return mat.numRows(); } 
    qlonglong colCount(void) const { return mat.numCols(); }

public:
    
};

// 
// dtkDenseMatrix.h ends here
