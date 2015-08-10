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

#include <flens/flens.cxx>

namespace dtk { namespace blas {

// ///////////////////////////////////////////////////////////////////
// ASUM
// ///////////////////////////////////////////////////////////////////


template <typename T, typename S> inline typename std::enable_if<dtkIsNotComplex<S>::value>::type asum(const dtkDenseVector<T>& x, S& absolute_sum)
{
    flens::blas::asum(x, absolute_sum);
}

template <typename T> inline const typename dtkComplex<T>::primitive_type asum(const dtkDenseVector<T>& x)
{
    typename dtkComplex<T>::primitive_type absolute_sum;
    asum(x, absolute_sum);
    return absolute_sum;
}

// ///////////////////////////////////////////////////////////////////
// AXPY
// ///////////////////////////////////////////////////////////////////

template <typename ALPHA, typename T1, typename T2> inline void axpy(const ALPHA &alpha, const dtkDenseVector<T1>& x, dtkDenseVector<T2>& y)
{
    flens::blas::axpy(alpha, x, y);
}

// ///////////////////////////////////////////////////////////////////
// COPY
// ///////////////////////////////////////////////////////////////////

template <typename T1, typename T2> inline void copy(const dtkDenseVector<T1>& x, dtkDenseVector<T2>& y)
{
    flens::blas::copy(x, y);
}

// ///////////////////////////////////////////////////////////////////
// DOT
// ///////////////////////////////////////////////////////////////////

template <typename T1, typename T2, typename T> inline void dot(const dtkDenseVector<T1>& x, const dtkDenseVector<T2>& y, T& result)
{
    flens::blas::dot(x, y, result);
}

template <typename T1, typename T2, typename T> inline void dotu(const dtkDenseVector<T1>& x, const dtkDenseVector<T2>& y, T& result)
{
    flens::blas::dotu(x, y, result);
}

template <typename T1, typename T2> inline typename dtkCompatibleType<T1, T2>::type dot(const dtkDenseVector<T1>& x, const dtkDenseVector<T2>& y)
{
    typename dtkCompatibleType<T1, T2>::type res;
    dot(x, y, res);
    return res;
}

template <typename T1, typename T2> inline typename dtkCompatibleType<T1, T2>::type dotu(const dtkDenseVector<T1>& x, const dtkDenseVector<T2>& y)
{
    typename dtkCompatibleType<T1, T2>::type res;
    dotu(x, y, res);
    return res;
}

// ///////////////////////////////////////////////////////////////////
// NRM2
// ///////////////////////////////////////////////////////////////////

template <typename T, typename S> inline typename std::enable_if<dtkIsNotComplex<S>::value>::type nrm2(const dtkDenseVector<T>& x, S& norm)
{
    flens::blas::nrm2(x, norm);
}

template <typename T, typename S> inline typename std::enable_if<dtkIsNotComplex<S>::value>::type normL2(const dtkDenseVector<T>& x, S& norm)
{
    flens::blas::nrm2(x, norm);
}

template <typename T> inline typename dtkComplex<T>::primitive_type nrm2(const dtkDenseVector<T>& x)
{
    typename dtkComplex<T>::primitive_type norm;
    nrm2(x, norm);
    return norm;
}

template <typename T> inline typename dtkComplex<T>::primitive_type normL2(const dtkDenseVector<T>& x)
{
    return nrm2(x);
}

// ///////////////////////////////////////////////////////////////////
// ROT
// ///////////////////////////////////////////////////////////////////

template <typename T> inline void rotg(T& a, T& b, T& c, T& s)
{
    flens::blas::rotg(a, b, c, s);
}

template <typename T> inline void rotg(std::complex<T>& a, std::complex<T>& b, T& c, std::complex<T>& s)
{
    flens::blas::rotg(a, b, c, s);
}

template <typename TX, typename TY, typename TC, typename TS> inline void rot(dtkDenseVector<TX>& x, dtkDenseVector<TY>& y, const TC& c, const TS& s)
{
    flens::blas::rot(x, y, c, s);
}

// ///////////////////////////////////////////////////////////////////
// ROTM
// ///////////////////////////////////////////////////////////////////

template <typename T, typename TP> inline void rotmg(T& d1, T& d2, T& b1, T& b2, dtkDenseVector<TP>& p)
{
    flens::blas::rotm(d1, d2, b1. b2, p);
}

template <typename TX, typename TY, typename TP> inline void rotm(dtkDenseVector<TX>& x, dtkDenseVector<TY>& y, const dtkDenseVector<TP>& p)
{
    flens::blas::rotm(x, y, p);
}

// ///////////////////////////////////////////////////////////////////
// SCAL
// ///////////////////////////////////////////////////////////////////

template <typename ALPHA, typename TY> inline void scal(const ALPHA& alpha, dtkDenseVector<TY>& y)
{
    flens::blas::scal(alpha, y);
}

// ///////////////////////////////////////////////////////////////////
// SWAP
// ///////////////////////////////////////////////////////////////////

template <typename TX, typename TY> inline void swap(dtkDenseVector<TX>& x, dtkDenseVector<TY>& y)
{
    flens::blas::swap(x, y);
}

// ///////////////////////////////////////////////////////////////////

} }

// 
// dtkBlasLevel1.tpp ends here
