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

// ///////////////////////////////////////////////////////////////////
// CRTP base class implementation
// ///////////////////////////////////////////////////////////////////

template < typename T > inline const typename flens::Vector< dtkDenseVector<T> >::Impl& flens::Vector< dtkDenseVector<T> >::impl(void) const
{
    return static_cast<const dtkDenseVector<T>&>(*this).impl();
}

template < typename T > inline typename flens::Vector< dtkDenseVector<T> >::Impl& flens::Vector< dtkDenseVector<T> >::impl(void)
{
    return static_cast<dtkDenseVector<T>&>(*this).impl();
}

// ///////////////////////////////////////////////////////////////////
// dtkDenseVector implementation
// ///////////////////////////////////////////////////////////////////

template < typename T > inline const typename dtkDenseVector<T>::FlensView& dtkDenseVector<T>::impl(void) const
{
    return *m_view;
}

template < typename T > inline typename dtkDenseVector<T>::FlensView& dtkDenseVector<T>::impl(void)
{
    return *m_view;
}

template < typename T > inline dtkDenseVector<T>::dtkDenseVector(void) : m_engine(NULL), m_view(NULL)
{

}

template < typename T > inline dtkDenseVector<T>::dtkDenseVector(qlonglong size) : m_array(size)
{
    m_engine = new Engine(size, const_cast<T *>(m_array.constData()));
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseVector<T>::dtkDenseVector(std::initializer_list<T> list) : m_array(list)
{
    m_engine = new Engine(m_array.size(), const_cast<T *>(m_array.constData()));
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseVector<T>::dtkDenseVector(const dtkDenseVector<T>& rhs) : m_array(rhs.data(), rhs.size())
{
    m_engine = new Engine(m_array.size(), const_cast<T *>(m_array.constData())), rhs.stride(), rhs.firstIndex();
    m_view   = new FlensView(*m_engine);
}

template < typename T > template < typename RHS > inline dtkDenseVector<T>::dtkDenseVector(const flens::Vector<RHS>& rhs) : m_array(rhs.impl().data(), rhs.impl().length())
{
    m_engine = new Engine(m_array.size(), const_cast<T *>(m_array.constData()), rhs.impl().stride(), rhs.impl().firstIndex());
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseVector<T>::dtkDenseVector(const T *data, qlonglong size, qlonglong stride, qlonglong first_index) : m_array(dtkArray<T>::fromRawData(data, size))
{
    m_engine = new Engine(size, const_cast<T *>(data), stride, first_index);
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseVector<T>::dtkDenseVector(T *data, qlonglong size, qlonglong stride, qlonglong first_index) : m_array(dtkArray<T>::fromWritableRawData(data, size))
{
    m_engine = new Engine(size, data, stride, first_index);
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseVector<T>::~dtkDenseVector(void)
{
    if (m_view)
        delete m_view;

    if (m_engine)
        delete m_engine;

    m_view    = NULL;
    m_engine = NULL;
}

template < typename T > inline dtkDenseVector<T>& dtkDenseVector<T>::operator = (const T& value)
{
    this->fill(value);
    return *this;
}

template < typename T > template < typename RHS > inline dtkDenseVector<T>& dtkDenseVector<T>::operator = (const flens::Vector<RHS>& rhs)
{
    *m_view = rhs.impl();
    return *this;
}

template < typename T > template < typename RHS > inline dtkDenseVector<T>& dtkDenseVector<T>::operator += (const flens::Vector<RHS>& rhs)
{
    *m_view += rhs;
    return *this;
}

template < typename T > template < typename RHS > inline dtkDenseVector<T>& dtkDenseVector<T>::operator -= (const flens::Vector<RHS>& rhs)
{
    *m_view -= rhs;
    return *this;
}

template < typename T > template < typename S > inline typename std::enable_if<std::is_convertible<S, T>::value, dtkDenseVector<T> >::type& dtkDenseVector<T>::operator *= (const S& alpha)
{
    *m_view *= alpha;
    return *this;
}

template < typename T > template < typename S > inline typename std::enable_if<std::is_convertible<S, T>::value, dtkDenseVector<T> >::type& dtkDenseVector<T>::operator /= (const S& alpha)
{
    *m_view /= alpha;
    return *this;
}

template < typename T > inline bool dtkDenseVector<T>::empty(void) const
{
    return !m_view->length();
}

template < typename T > inline qlonglong dtkDenseVector<T>::size(void) const
{
    return m_view->length();
}

template < typename T > inline qlonglong dtkDenseVector<T>::length(void) const
{
    return m_view->length();
}

template < typename T > inline qlonglong dtkDenseVector<T>::stride(void) const
{
    return m_view->stride();
}

template < typename T > inline qlonglong dtkDenseVector<T>::firstIndex(void) const
{
    return m_view->firstIndex();
}

template < typename T > inline qlonglong dtkDenseVector<T>::lastIndex(void) const
{
    return m_view->lastIndex();
}

template < typename T > inline void dtkDenseVector<T>::resize(const qlonglong& size)
{
    if (size != this->size()) {
        m_array.resize(size);

        if (m_view)
            delete m_view;
        if (m_engine)
            delete m_engine;

        m_engine = new Engine(m_array.size(), m_array.data());
        m_view   = new FlensView(*m_engine);
    }
}

template < typename T > inline void dtkDenseVector<T>::append(std::initializer_list<T> list)
{
    if (list.size() > 0) {
        m_array.append(list);

        if (m_view)
            delete m_view;
        if (m_engine)
            delete m_engine;

        m_engine = new Engine(m_array.size(), m_array.data());
        m_view   = new FlensView(*m_engine);
    }
}

template < typename T > inline void dtkDenseVector<T>::fill(const T& value)
{
    m_view->fill(value);
}

template < typename T > inline void dtkDenseVector<T>::setAt(const qlonglong& index, const T& value)
{
    (*m_view)(index) = value;
}

template < typename T > inline const T& dtkDenseVector<T>::at(const qlonglong& index) const
{
    return (*m_view)(index);
}

template < typename T > inline const T& dtkDenseVector<T>::first(void) const
{
    return this->at(this->firstIndex());
}

template < typename T > inline const T& dtkDenseVector<T>::last(void) const
{
    return this->at(this->lastIndex());
}

template < typename T > inline const T& dtkDenseVector<T>::operator [] (qlonglong index) const
{
    return (*m_view)(index);
}

template < typename T > inline T& dtkDenseVector<T>::operator [] (qlonglong index)
{
    return (*m_view)(index);
}

template < typename T > inline const T& dtkDenseVector<T>::operator () (qlonglong index) const
{
    return (*m_view)(index);
}

template < typename T > inline T& dtkDenseVector<T>::operator () (qlonglong index)
{
    return (*m_view)(index);
}

template < typename T > inline const T *dtkDenseVector<T>::data(void) const
{
    return m_view->data();
}

template < typename T > inline T *dtkDenseVector<T>::data(void)
{
    return m_view->data();
}

template < typename T > inline const T *dtkDenseVector<T>::constData(void) const
{
    return m_view->data();
}

template < typename T > inline const typename dtkDenseVector<T>::ConstView dtkDenseVector<T>::operator() (const Range& range) const
{
    return this->operator() (range, this->firstIndex());
}

template < typename T > inline typename dtkDenseVector<T>::View dtkDenseVector<T>::operator() (const Range& range)
{
    return this->operator() (range, this->firstIndex());
}

template < typename T > inline const typename dtkDenseVector<T>::ConstView dtkDenseVector<T>::operator() (const Range& range, qlonglong first_index) const
{
        qlonglong from   = range.firstIndex();
        qlonglong to     = range.lastIndex();
        qlonglong stride = range.stride();

        qlonglong length = (to - from) / stride + 1;

        const T *begin = &operator()(from);

        return ConstView(begin, length, stride * this->stride(), first_index);
}

template < typename T > inline typename dtkDenseVector<T>::View dtkDenseVector<T>::operator() (const Range& range, qlonglong first_index)
{
        qlonglong from = range.firstIndex();
        qlonglong to   = range.lastIndex();
        qlonglong stride = range.stride();

        qlonglong length = (to - from) / stride + 1;

        T *begin = &operator()(from);

        return View(begin, length, stride * this->stride(), first_index);
}

template < typename T > inline const typename dtkDenseVector<T>::ConstView dtkDenseVector<T>::operator() (const Underscore& all, qlonglong first_index) const
{
    return this->operator()(all(this->firstIndex(), 1LL, this->lastIndex()), first_index);
}

template < typename T > inline typename dtkDenseVector<T>::View dtkDenseVector<T>::operator() (const Underscore& all, qlonglong first_index)
{
    return this->operator()(all(this->firstIndex(), 1LL, this->lastIndex()), first_index);
}

// ///////////////////////////////////////////////////////////////////
// dtkDenseVector::View implementation
// ///////////////////////////////////////////////////////////////////

template < typename T > inline dtkDenseVector<T>::View::View(T *data, qlonglong size, qlonglong stride, qlonglong first_index) : dtkDenseVector<T>(data, size, stride, first_index)
{

}

template < typename T > inline dtkDenseVector<T>::View::View(const View& rhs) : dtkDenseVector<T>(rhs.data(), rhs.size(), rhs.stride(), rhs.firstIndex())
{

}

// ///////////////////////////////////////////////////////////////////
// dtkDenseVector::ConstView implementation
// ///////////////////////////////////////////////////////////////////

template < typename T > inline dtkDenseVector<T>::ConstView::ConstView(const T *data, qlonglong size, qlonglong stride, qlonglong first_index) : dtkDenseVector<T>(data, size, stride, first_index)
{

}

template < typename T > inline dtkDenseVector<T>::ConstView::ConstView(const ConstView& rhs) : dtkDenseVector<T>(rhs.data(), rhs.size(), rhs.stride(), rhs.firstIndex())
{

}

template < typename T > inline dtkDenseVector<T>::ConstView::ConstView(const View& rhs) : dtkDenseVector<T>(rhs.data(), rhs.size(), rhs.stride(), rhs.firstIndex())
{

}

//
// dtkDenseVector.tpp ends here
