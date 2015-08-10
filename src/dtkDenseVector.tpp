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

// ///////////////////////////////////////////////////////////////////
// Raw data initialization
// ///////////////////////////////////////////////////////////////////

template < typename T > inline dtkDenseVectorView<T> dtkVectorFromWritableRawData(qlonglong size, T *data)
{
    return dtkDenseVectorView<T>(flens::ArrayView<T>(size, data));
}

template < typename T > inline dtkDenseVectorConstView<T> dtkVectorFromRawData(qlonglong size, const T *data)
{
    return dtkDenseVectorConstView<T>(flens::ConstArrayView<T>(size, data));
}

// 
// dtkDenseVector.tpp ends here
