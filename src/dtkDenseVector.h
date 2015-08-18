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
    typedef dtkDenseVectorView<T> Impl;

    virtual ~Vector(void) {}

    const Impl& impl(void) const;
          Impl& impl(void);
};
}

// ///////////////////////////////////////////////////////////////////
// Wrapper dtkDenseVec
// ///////////////////////////////////////////////////////////////////

template < typename T > class dtkDenseVec : public flens::Vector< dtkDenseVec<T> >
{
    dtkDenseVectorView<T> *m_vec;
    typedef typename dtkDenseVectorView<T>::Engine Engine;
    Engine *m_engine;
    dtkArray<T> m_array;

public:
    typedef flens::Range<qlonglong> Range;

public:
    friend class flens::Vector< dtkDenseVec<T> >;
    const dtkDenseVectorView<T>& impl(void) const { return *m_vec; }
          dtkDenseVectorView<T>& impl(void)       { return *m_vec; }

public:
    dtkDenseVec(void) : m_engine(0), m_vec(0) {;}
    dtkDenseVec(qlonglong size) : m_array(size) { m_engine = new Engine(size, m_array.data()); m_vec = new dtkDenseVectorView<T>(*m_engine); }
    dtkDenseVec(const dtkDenseVec<T>& rhs) : m_array(rhs.data(), rhs.size()) { qDebug()<<Q_FUNC_INFO;m_engine = new Engine(m_array.size(), m_array.data(), rhs.stride()); m_vec = new dtkDenseVectorView<T>(*m_engine); }

public:
    template <typename RHS> dtkDenseVec(const flens::Vector<RHS>& rhs) : m_array(rhs.impl().data(), rhs.impl().length()) { m_engine = new Engine(m_array.size(), m_array.data(), rhs.impl().stride(), rhs.impl().firstIndex()); m_vec = new dtkDenseVectorView<T>(*m_engine); }

protected:
    dtkDenseVec(const dtkArray<T>& array, Engine *engine, dtkDenseVectorView<T> *vec) : m_array(array), m_engine(engine), m_vec(vec) {;}

public:
    ~dtkDenseVec(void) { if(m_vec) delete m_vec; if (m_engine) delete m_engine; }

public:
                            dtkDenseVec& operator  = (const dtkDenseVec& rhs)        { *m_vec = *(rhs.m_vec); return *this; }
    template <typename RHS> dtkDenseVec& operator  = (const flens::Vector<RHS>& rhs) { *m_vec = rhs; return *this; }

    template <typename RHS> dtkDenseVec& operator += (const flens::Vector<RHS>& rhs) { *m_vec += rhs; return *this; }
    template <typename RHS> dtkDenseVec& operator -= (const flens::Vector<RHS>& rhs) { *m_vec -= rhs; return *this; }

public:
    template <typename S> typename std::enable_if<std::is_convertible<S, T>::value, dtkDenseVec>::type& operator *= (const S& alpha) { *m_vec *= alpha; return *this; }
    template <typename S> typename std::enable_if<std::is_convertible<S, T>::value, dtkDenseVec>::type& operator /= (const S& alpha) { *m_vec /= alpha; return *this; }

public:
    bool empty(void) const { return !m_vec->length(); }

    qlonglong   size(void) const { return m_vec->length(); }
    qlonglong length(void) const { return m_vec->length(); }

    qlonglong stride(void) const { return m_vec->stride(); }

public:
    void resize(const qlonglong& size) { 
        m_array.resize(size); 
        if (m_vec) delete m_vec; 
        if(m_engine) delete m_engine; 
        m_engine = new Engine(m_array.size(), m_array.data());
        m_vec = new dtkDenseVectorView<T>(*m_engine);
    }

public:
    void fill(const T& value) { m_vec->fill(value); }

public:
    void setAt(const qlonglong& index, const T& value) { (*m_vec)(index) = value; }

    T at(const qlonglong& index) const { return (*m_vec)(index); }

    T first(void) const { return (*m_vec)(m_vec->firstIndex()); }
    T  last(void) const { return (*m_vec)(m_vec->lastIndex());  }

public:
    const T& operator [] (qlonglong index) const { return (*m_vec)(index); }
          T& operator [] (qlonglong index)       { return (*m_vec)(index); }
    
public:
    const T& operator () (qlonglong index) const { return  (*m_vec)(index); }
          T& operator () (qlonglong index)       { return  (*m_vec)(index); }
    
public:
    const T *data(void) const { return m_vec->data(); }
          T *data(void)       { return m_vec->data(); }

    const T *constData(void) const { return m_vec->data(); }

public:
    class View;
    
public:
    const dtkDenseVec<T>::View operator() (const Range& range) const {

        qlonglong from = range.firstIndex();
        qlonglong to   = range.lastIndex();
        qlonglong stride = range.stride();

        qlonglong length = (to - from) / stride + 1;

        dtkArray<T> array = dtkArray<T>::fromRawData(data(), size());

        T *begin = const_cast<T *>(array.constData() + (from - 1));
        Engine *engine = new Engine(length, begin, stride, m_vec->firstIndex());
        dtkDenseVectorView<T> *vec = new dtkDenseVectorView<T>(*engine);        

        const dtkDenseVec<T>::View v_view(array, engine, vec);

        return v_view;
    }

    dtkDenseVec<T>::View operator() (const Range& range) {

        qlonglong from = range.firstIndex();
        qlonglong to   = range.lastIndex();
        qlonglong stride = range.stride();

        qlonglong length = (to - from) / stride + 1;

        dtkArray<T> array = dtkArray<T>::fromWritableRawData(data(), size());

        T *begin = array.data() + (from - 1);
        Engine *engine = new Engine(length, begin, stride, m_vec->firstIndex());
        dtkDenseVectorView<T> *vec = new dtkDenseVectorView<T>(*engine);        

        dtkDenseVec<T>::View v_view(array, engine, vec);

        return v_view;        
    }
};

template <typename T> class dtkDenseVec<T>::View : public dtkDenseVec<T>
{
public:
    View(const dtkArray<T>& array, Engine *engine, dtkDenseVectorView<T> *vec) : dtkDenseVec<T>(array, engine, vec) {;}
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
