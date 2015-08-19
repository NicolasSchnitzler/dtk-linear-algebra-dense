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
    typedef flens::Underscore<qlonglong> Underscore;

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
    dtkDenseVec(const T *data, qlonglong size, qlonglong stride, qlonglong first_index) : m_array(dtkArray<T>::fromRawData(data, size)), m_engine(new Engine(size, const_cast<T *>(data), stride, first_index)) { m_vec = new dtkDenseVectorView<T>(*m_engine); }
    dtkDenseVec(T *data, qlonglong size, qlonglong stride, qlonglong first_index) : m_array(dtkArray<T>::fromWritableRawData(data, size)), m_engine(new Engine(size, data, stride, first_index)) { m_vec = new dtkDenseVectorView<T>(*m_engine); }

public:
    ~dtkDenseVec(void) { if(m_vec) delete m_vec; if (m_engine) delete m_engine; }

public:
    typename dtkDenseVectorView<T>::Initializer operator = (const T& value) { fill(value); return typename dtkDenseVectorView<T>::Initializer(*m_vec, firstIndex()); }

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
    qlonglong firstIndex(void) const { return m_vec->firstIndex(); }
    qlonglong  lastIndex(void) const { return m_vec->lastIndex();  }

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
    class ConstView;

public:
    const dtkDenseVec<T>::ConstView operator() (const Range& range) const {
        return this->operator() (range, this->firstIndex());
    }

    dtkDenseVec<T>::View operator() (const Range& range) {
        return this->operator() (range, this->firstIndex());
    }

    const dtkDenseVec<T>::ConstView operator() (const Range& range, qlonglong first_index) const {

        qlonglong from = range.firstIndex();
        qlonglong to   = range.lastIndex();
        qlonglong stride = range.stride();

        qlonglong length = (to - from) / stride + 1;

        const T *begin = &operator()(from);

        return dtkDenseVec<T>::ConstView(begin, length, stride * this->stride(), first_index);
    }

    dtkDenseVec<T>::View operator() (const Range& range, qlonglong first_index) {

        qlonglong from = range.firstIndex();
        qlonglong to   = range.lastIndex();
        qlonglong stride = range.stride();

        qlonglong length = (to - from) / stride + 1;

        T *begin = &operator()(from);

        dtkDenseVec<T>::View v_view(begin, length, stride * this->stride(), first_index);

        return v_view;
    }

    const ConstView operator() (const Underscore& all, qlonglong first_index) const {
        return this->operator()(all(this->firstIndex(), 1LL, this->lastIndex()), first_index);
    }

    View operator() (const Underscore& all, qlonglong first_index) {
        return this->operator()(all(this->firstIndex(), 1LL, this->lastIndex()), first_index);
    }
};

template <typename T> class dtkDenseVec<T>::View : public dtkDenseVec<T>
{
public:
    View(const T *data, qlonglong size, qlonglong stride, qlonglong first_index) : dtkDenseVec<T>(data, size, stride, first_index) {;}
    View(T *data, qlonglong size, qlonglong stride, qlonglong first_index) : dtkDenseVec<T>(data, size, stride, first_index) {;}
    View(const View& rhs) : dtkDenseVec<T>(rhs.data(), rhs.size(), rhs.stride(), rhs.firstIndex()) {;}

private:
    void resize(qlonglong) {;}
};

template <typename T> class dtkDenseVec<T>::ConstView : private dtkDenseVec<T>
{
public:
    ConstView(const T *data, qlonglong size, qlonglong stride, qlonglong first_index) : dtkDenseVec<T>(data, size, stride, first_index) {;}
    ConstView(const ConstView& rhs) : dtkDenseVec<T>(rhs.data(), rhs.size(), rhs.stride(), rhs.firstIndex()) {;}
    ConstView(const View& rhs) : dtkDenseVec<T>(rhs.data(), rhs.size(), rhs.stride(), rhs.firstIndex()) {;}

public:
    const dtkDenseVectorView<T>& impl(void) const { return dtkDenseVec<T>::impl(); }
          dtkDenseVectorView<T>& impl(void)       { return dtkDenseVec<T>::impl(); }

public:
    bool empty(void) const { return dtkDenseVec<T>::empty(); }

    qlonglong   size(void) const { return dtkDenseVec<T>::size(); }
    qlonglong length(void) const { return dtkDenseVec<T>::size(); }

    qlonglong stride(void) const { return dtkDenseVec<T>::stride(); }

public:
    T at(const qlonglong& index) const { return dtkDenseVec<T>::at(index); }

    T first(void) const { return dtkDenseVec<T>::first(); }
    T  last(void) const { return dtkDenseVec<T>::last(); }

public:
    const T& operator [] (qlonglong index) const { return dtkDenseVec<T>::operator[](index); }

public:
    const T& operator () (qlonglong index) const { return dtkDenseVec<T>::operator()(index); }

public:
    const T *data(void) const { return dtkDenseVec<T>::data(); }

    const T *constData(void) const { return dtkDenseVec<T>::constData(); }

public:
    const dtkDenseVec<T>::ConstView operator() (const Range& range) const { return dtkDenseVec<T>::operator() (range); }
    const dtkDenseVec<T>::ConstView operator() (const Range& range, qlonglong first_index) const { return dtkDenseVec<T>::operator() (range, first_index); }
    const ConstView operator() (const Underscore& all, qlonglong first_index) const { return dtkDenseVec<T>::operator() (all, first_index); }
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
