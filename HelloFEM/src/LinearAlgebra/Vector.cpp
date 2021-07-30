#include "Vector.h"


template <typename AllocatorType>
template <typename AllocatorType1>
void Vector<AllocatorType>::CopyVector(const Vector<AllocatorType1>& src)
{
    const DataType* v1 = src.Data();
    DataType* v0 = Data();

    for (int i = 0; i < m_Size; i++)
    {
        v0[i] = v1[i];
    }
}

template <typename AllocatorType>
void Vector<AllocatorType>::Resize(int size)
{
    if (m_Size == size) return;
    DeAllocate();
    m_Size = size;
    Allocate(m_Size);
}

template <typename AllocatorType>
Vector<AllocatorType>& Vector<AllocatorType>::operator=(const Vector& other)
{
    Resize(other.Size());
    CopyVector(other);
    return *this;
}

template <typename AllocatorType>
template <typename AllocatorType1>
Vector<AllocatorType>& Vector<AllocatorType>::operator=(const Vector<AllocatorType1>& other)
{
    Resize(other.Size());
    CopyVector(other);
    return *this;
}

template <typename AllocatorType>
template <typename VectorType1, typename VectorType2, typename OprType>
Vector<AllocatorType>& Vector<AllocatorType>::operator=(const Vec2Expr<VectorType1, VectorType2, OprType>& vov)
{
    DataType* v3 = Data();
    for (int i = 0; i < m_Size; i++)
    {
        v3[i] = vov[i];
    }

    return *this;
}