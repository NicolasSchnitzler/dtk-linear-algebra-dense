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
#include "dtkDenseVector.h"

namespace dtk { namespace blas {

// ///////////////////////////////////////////////////////////////////
// ASUM
// ///////////////////////////////////////////////////////////////////

template <typename T, typename S> typename std::enable_if<dtkIsNotComplex<S>::value>::type asum(const dtkDenseVector<T>& x, S& absolute_sum);

template <typename T> const typename dtkComplex<T>::primitive_type asum(const dtkDenseVector<T>& x);


// ///////////////////////////////////////////////////////////////////
// AXPY
// ///////////////////////////////////////////////////////////////////

template <typename ALPHA, typename T1, typename T2> void axpy(const ALPHA &alpha, const dtkDenseVector<T1>& x, dtkDenseVector<T2>& y);


// ///////////////////////////////////////////////////////////////////
// COPY
// ///////////////////////////////////////////////////////////////////

template <typename T1, typename T2> void copy(const dtkDenseVector<T1>& x, dtkDenseVector<T2>& y);


// ///////////////////////////////////////////////////////////////////
// DOT
// ///////////////////////////////////////////////////////////////////

template <typename T1, typename T2, typename T> void  dot(const dtkDenseVector<T1>& x, const dtkDenseVector<T2>& y, T& result);
template <typename T1, typename T2, typename T> void dotu(const dtkDenseVector<T1>& x, const dtkDenseVector<T2>& y, T& result);

template <typename T1, typename T2> typename dtkCompatibleType<T1, T2>::type  dot(const dtkDenseVector<T1>& x, const dtkDenseVector<T2>& y);
template <typename T1, typename T2> typename dtkCompatibleType<T1, T2>::type dotu(const dtkDenseVector<T1>& x, const dtkDenseVector<T2>& y);


// ///////////////////////////////////////////////////////////////////
// NRM2
// ///////////////////////////////////////////////////////////////////

template <typename T, typename S> typename std::enable_if<dtkIsNotComplex<S>::value>::type   nrm2(const dtkDenseVector<T>& x, S& norm);
template <typename T, typename S> typename std::enable_if<dtkIsNotComplex<S>::value>::type normL2(const dtkDenseVector<T>& x, S& norm);

template <typename T> typename dtkComplex<T>::primitive_type   nrm2(const dtkDenseVector<T>& x);
template <typename T> typename dtkComplex<T>::primitive_type normL2(const dtkDenseVector<T>& x);


// ///////////////////////////////////////////////////////////////////
// ROT
// ///////////////////////////////////////////////////////////////////

template <typename T> void rotg(T& a, T& b, T& c, T& s);
template <typename T> void rotg(std::complex<T>& a, std::complex<T>& b, T& c, std::complex<T>& s);

template <typename TX, typename TY, typename TC, typename TS> void rot(dtkDenseVector<TX>& x, dtkDenseVector<TY>& y, const TC& c, const TS& s);


// ///////////////////////////////////////////////////////////////////
// ROTM
// ///////////////////////////////////////////////////////////////////

template <typename T, typename TP> void rotmg(T& d1, T& d2, T& b1, T& b2, dtkDenseVector<TP>& p);

template <typename TX, typename TY, typename TP> void rotm(dtkDenseVector<TX>& x, dtkDenseVector<TY>& y, const dtkDenseVector<TP>& p);
template <typename TX, typename TY, typename TC, typename TS> void rot(dtkDenseVector<TX>& x, dtkDenseVector<TY>& y, const TC& c, const TS& s);


// ///////////////////////////////////////////////////////////////////
// SCAL
// ///////////////////////////////////////////////////////////////////

template <typename ALPHA, typename TY> void scal(const ALPHA& alpha, dtkDenseVector<TY>& y);


// ///////////////////////////////////////////////////////////////////
// SWAP
// ///////////////////////////////////////////////////////////////////

template <typename TX, typename TY> void swap(dtkDenseVector<TX>& x, dtkDenseVector<TY>& y);

// ///////////////////////////////////////////////////////////////////

} }

// ///////////////////////////////////////////////////////////////////

#include "dtkBlasLevel1.tpp"

// 
// dtkBlasLevel1.h ends here
