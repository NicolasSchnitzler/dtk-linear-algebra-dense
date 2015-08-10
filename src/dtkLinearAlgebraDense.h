// Version: $Id: 
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

#include <type_traits>
#include <complex>

// ///////////////////////////////////////////////////////////////////
// Compatible type
// ///////////////////////////////////////////////////////////////////

template <typename T1, typename T2> struct dtkCompatibleType {};

template <typename T> struct dtkCompatibleType<T, T>
{
    typedef T type;
};

template <> struct dtkCompatibleType<double, float>
{
    typedef double type;
};

template <> struct dtkCompatibleType<float, double>
{
    typedef double type;
};

template <typename T> struct dtkCompatibleType< std::complex<T>, T >
{
    typedef std::complex<T> type;
};

template <typename T> struct dtkCompatibleType< T , std::complex<T> >
{
    typedef std::complex<T> type;
};

// ///////////////////////////////////////////////////////////////////
// Complex traits
// ///////////////////////////////////////////////////////////////////

template< typename T > struct dtkIsComplex : std::false_type {};
template< typename T > struct dtkIsComplex< std::complex<T> > : std::true_type {};

template< typename T > struct dtkIsNotComplex : std::true_type {};
template< typename T > struct dtkIsNotComplex< std::complex<T> > : std::false_type {};

template< typename T > struct dtkComplex
{
    typedef T primitive_type;
};

template< typename T > struct dtkComplex< std::complex<T> >
{
    typedef T primitive_type;
};


//
// dtkLinearAlgebraDense.h ends here
