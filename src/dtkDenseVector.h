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

// ///////////////////////////////////////////////////////////////////
// Alias
// ///////////////////////////////////////////////////////////////////

template < typename T > using dtkDenseVector = flens::DenseVector< flens::Array<T> >;
template < typename T > using dtkDenseVectorView = flens::DenseVector< flens::ArrayView<T> >;
template < typename T > using dtkDenseVectorConstView = flens::DenseVector< flens::ConstArrayView<T> >;

// ///////////////////////////////////////////////////////////////////
// Raw data initialization
// ///////////////////////////////////////////////////////////////////

template < typename T > dtkDenseVectorView<T> dtkVectorFromWritableRawData(qlonglong size, T *data);
template < typename T > dtkDenseVectorConstView<T> dtkVectorFromRawData(qlonglong size, const T *data);

// ///////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////
// Template specialization for flens::Vector< dtkDenseVec<T> >
// ///////////////////////////////////////////////////////////////////

template < typename T > class dtkDenseVec;

namespace flens {

template < typename T > class Vector< dtkDenseVec<T> >
{
public:
    typedef dtkDenseVector<T> Impl;

    virtual ~Vector() {}

    const Impl& impl(void) const;
          Impl& impl(void);
};
}

// ///////////////////////////////////////////////////////////////////
// Wrapper dtkDenseVec
// ///////////////////////////////////////////////////////////////////

template < typename T > class dtkDenseVec : public flens::Vector< dtkDenseVec<T> >
{
    dtkDenseVector<T> m_vec;

public:
    const dtkDenseVector<T>& impl(void) const { return m_vec; } 
          dtkDenseVector<T>& impl(void)       { return m_vec; } 

public:
    dtkDenseVec(void) {;}
    dtkDenseVec(qlonglong size) : m_vec(size) {}
    dtkDenseVec(const dtkDenseVec& rhs) : m_vec(rhs.m_vec) {}

public:
    template <typename RHS> dtkDenseVec(const flens::Vector<RHS>& rhs) : m_vec(rhs) {}

public:
                            dtkDenseVec& operator  = (const dtkDenseVec& rhs)        { m_vec = rhs.m_vec; return *this; }
    template <typename RHS> dtkDenseVec& operator  = (const flens::Vector<RHS>& rhs) { m_vec = rhs; return *this; }

    template <typename RHS> dtkDenseVec& operator += (const flens::Vector<RHS>& rhs) { m_vec += rhs; return *this; }
    template <typename RHS> dtkDenseVec& operator -= (const flens::Vector<RHS>& rhs) { m_vec -= rhs; return *this; }

public:
    template <typename S> typename std::enable_if<std::is_convertible<S, T>::value, dtkDenseVec>::type& operator *= (const S& alpha) { m_vec *= alpha; return *this; }
    template <typename S> typename std::enable_if<std::is_convertible<S, T>::value, dtkDenseVec>::type& operator /= (const S& alpha) { m_vec /= alpha; return *this; }
    
public:
    const T& operator () (qlonglong index) const { return m_vec(index); }
          T& operator () (qlonglong index)       { return m_vec(index); }

public:
    qlonglong   size(void) const { return m_vec.length(); }
    qlonglong length(void) const { return m_vec.length(); }

public:
    void fill(const T& value) { m_vec.fill(value); }
    
public:
    const T *data(void) const { return m_vec.data(); }
          T *data(void)       { return m_vec.data(); }
};

// ///////////////////////////////////////////////////////////////////

template < typename T > inline const typename flens::Vector< dtkDenseVec<T> >::Impl& flens::Vector< dtkDenseVec<T> >::impl(void) const
{
    return static_cast<const dtkDenseVec<T>&>(*this).impl();
}

template < typename T > inline typename flens::Vector< dtkDenseVec<T> >::Impl& flens::Vector< dtkDenseVec<T> >::impl(void)
{
    return static_cast<dtkDenseVec<T>&>(*this).impl();
}

// ///////////////////////////////////////////////////////////////////

#include "dtkDenseVector.tpp"

// 
// dtkDenseVector.h ends here
