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

template < typename T > inline const typename dtkMatrixBase<T>::Impl& dtkMatrixBase<T>::impl(void) const
{
    return static_cast<const dtkDenseMatrix<T>&>(*this).impl();
}

template < typename T > inline typename dtkMatrixBase<T>::Impl& dtkMatrixBase<T>::impl(void)
{
    return static_cast<dtkDenseMatrix<T>&>(*this).impl();
}


// ///////////////////////////////////////////////////////////////////
// dtkDenseMatrix implementation
// ///////////////////////////////////////////////////////////////////

template < typename T > inline const typename dtkDenseMatrix<T>::FlensView& dtkDenseMatrix<T>::impl(void) const
{
    return *m_view;
}

template < typename T > inline typename dtkDenseMatrix<T>::FlensView& dtkDenseMatrix<T>::impl(void)
{
    return *m_view;
}

template < typename T > inline dtkDenseMatrix<T>::dtkDenseMatrix(void)
{
    m_engine = new Engine(0, 0, const_cast<T *>(m_array.constData()), 0);
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseMatrix<T>::dtkDenseMatrix(qlonglong row_count,qlonglong col_count) : m_array(row_count*col_count)
{
    m_engine = new Engine(row_count, col_count, const_cast<T *>(m_array.constData()), row_count);
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseMatrix<T>::dtkDenseMatrix(const dtkDenseMatrix<T>& rhs) : m_array(rhs.data(), rhs.colCount()*rhs.rowCount())
{
    m_engine = new Engine(m_array.size(), const_cast<T *>(m_array.constData()), rhs.leadingDimension(), rhs.firstRow(), rhs.firstCol());
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseMatrix<T>::dtkDenseMatrix(const T *data, qlonglong row_count, qlonglong col_count, qlonglong first_row, qlonglong first_col) : m_array(dtkArray<T>::fromRawData(data, row_count*col_count))
{
    m_engine = new Engine(row_count, col_count, const_cast<T *>(data), row_count, first_row, first_col);
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseMatrix<T>::dtkDenseMatrix(T *data, qlonglong row_count, qlonglong col_count, qlonglong first_row, qlonglong first_col) : m_array(dtkArray<T>::fromRawData(data, row_count*col_count))
{
    m_engine = new Engine(row_count, col_count, const_cast<T *>(data), row_count, first_row, first_col);
    m_view   = new FlensView(*m_engine);
}

template < typename T > inline dtkDenseMatrix<T>::~dtkDenseMatrix(void)
{
    if (m_view)
        delete m_view;

    if (m_engine)
        delete m_engine;

    m_view   = NULL;
    m_engine = NULL;
}

template < typename T > inline bool dtkDenseMatrix<T>::isEmpty(void) const
{
    return m_view->numRows()==0 || m_view->numCols()==0;
}

template < typename T > inline qlonglong dtkDenseMatrix<T>::rowCount(void) const
{
    return m_view->numRows();
}

template < typename T > inline qlonglong dtkDenseMatrix<T>::colCount(void) const
{
    return m_view->numCols();
}

template < typename T > inline qlonglong dtkDenseMatrix<T>::firstRow(void) const 
{
    return m_view->firstRow();
}

template < typename T > inline qlonglong dtkDenseMatrix<T>::firstCol(void) const 
{
    return m_view->firstCol();
}


template < typename T > inline void dtkDenseMatrix<T>::fill(T value)
{
    m_view->fill(value);
}

template < typename T > inline const T& dtkDenseMatrix<T>::operator () (qlonglong row_id, qlonglong col_id) const
{
    return (*m_view)(row_id, col_id);
}

template < typename T > inline T& dtkDenseMatrix<T>::operator () (qlonglong row_id, qlonglong col_id)
{
    return (*m_view)(row_id, col_id);
}

template < typename T > inline const T *dtkDenseMatrix<T>::data(void) const
{
    return m_view->data();
}

template < typename T > inline T *dtkDenseMatrix<T>::data(void)
{
    return m_view->data();
}

template < typename T > inline const T *dtkDenseMatrix<T>::constData(void) const
{
    return m_view->data();
}

template < typename T > inline const typename dtkDenseMatrix<T>::ConstView dtkDenseMatrix<T>::operator() (const Range& row_range, const Range& col_range) const
{
    return this->operator() (row_range, col_range, m_view->firstRow(), m_view->firstCol());
}

template < typename T > inline typename dtkDenseMatrix<T>::View dtkDenseMatrix<T>::operator() (const Range& row_range, const Range& col_range)
{
    return this->operator() (row_range, col_range, m_view->firstRow(), m_view->firstCol());
}

template < typename T > inline const typename dtkDenseMatrix<T>::ConstView dtkDenseMatrix<T>::operator() (const Range& row_range, const Range& col_range, qlonglong first_row, qlonglong first_col) const
{
        qlonglong from_col   = col_range.firstIndex();
        qlonglong to_col     = col_range.lastIndex();

        qlonglong from_row   = row_range.firstIndex();
        qlonglong to_row     = row_range.lastIndex();

        const T *begin = &operator()(from_row,from_col);

        return ConstView(begin, to_row-from_row, to_col-from_col, first_row, first_col);
}

template < typename T > inline typename dtkDenseMatrix<T>::View dtkDenseMatrix<T>::operator() (const Range& row_range, const Range& col_range, qlonglong first_row, qlonglong first_col)
{
        qlonglong from_col   = col_range.firstIndex();
        qlonglong to_col     = col_range.lastIndex();

        qlonglong from_row   = row_range.firstIndex();
        qlonglong to_row     = row_range.lastIndex();

        T *begin = &operator()(from_row,from_col);

        return View(begin, to_row-from_row, to_col-from_col, first_row, first_col);
}

// ///////////////////////////////////////////////////////////////////
// dtkDenseMatrix::View implementation
// ///////////////////////////////////////////////////////////////////

template < typename T > inline dtkDenseMatrix<T>::View::View(T *data, qlonglong row_count, qlonglong col_count, qlonglong first_row, qlonglong first_col) : dtkDenseMatrix<T>(data, row_count, col_count, first_row, first_col)
{

}

template < typename T > inline dtkDenseMatrix<T>::View::View(const View& rhs) : dtkDenseMatrix<T>(rhs.data(), rhs.rowCount(), rhs.colCount(),rhs.firstRow(),rhs.firstCol())
{

}

// ///////////////////////////////////////////////////////////////////
// dtkDenseMatrix::ConstView implementation
// ///////////////////////////////////////////////////////////////////

template < typename T > inline dtkDenseMatrix<T>::ConstView::ConstView(T *data, qlonglong row_count, qlonglong col_count, qlonglong first_row, qlonglong first_col) : dtkDenseMatrix<T>(data, row_count, col_count, first_row, first_col)
{

}

template < typename T > inline dtkDenseMatrix<T>::ConstView::ConstView(const ConstView& rhs) : dtkDenseMatrix<T>(rhs.data(), rhs.rowCount(), rhs.colCount(),rhs.firstRow(),rhs.firstCol())
{

}

template < typename T > inline dtkDenseMatrix<T>::ConstView::ConstView(const View& rhs) : dtkDenseMatrix<T>(rhs.data(), rhs.rowCount(), rhs.colCount(),rhs.firstRow(),rhs.firstCol())
{

}


























