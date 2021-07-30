#pragma once

#ifdef _CHECK_RANGE
#define VectorAssert(cond) assert(cond)
#else
#define VectorAssert(cond)
#endif

#include "ArrayAllocator.h"
#include "Range.h"
#include "VectorCommaAssignment.h"
#include "VectorEvaluation.h"


template <typename AllocatorType = DynamicAllocator<double>>
class Vector : public AllocatorType 
{
private:
    int m_Size;

    template <typename AllocatorType1>
    void CopyVector(const Vector<AllocatorType1>& src);

public:
    typedef typename AllocatorType::MemberType DataType;
    typedef typename AllocatorType::MemberType TNumType;

    typedef DataType* Iterator;
    typedef const DataType* ConstIterator;

    Iterator Begin() { return Data(); }
    Iterator End() { return Data() + Size(); }  // Size() required
    ConstIterator Begin() const { return Data(); }
    ConstIterator End() const { return Data() + Size(); }

    // Constructors
    Vector()
        : m_Size(AllocatorType::DEFAULT_SIZE), AllocatorType() {}

    Vector(int size)
        : m_Size(size), AllocatorType(size) {}

    Vector(const DataType* pDataType, int size)
        : m_Size(size), AllocatorType(const_cast<DataType*>(pDataType)) {}

    Vector(const Vector<AllocatorType>& other)
        : m_Size(other.m_Size), AllocatorType(other.m_Size)
    {
        CopyVector(other);
    }

    ~Vector() { DeAllocate(); }

    void Resize(int size);
    void Clear() { Resize(0); }
    int Size() const { return m_Size; }
    int Stride() const { return 1; }

    void Swap(Vector& other) 
    { 
        std::swap(m_Size, other.m_Size);
        AllocatorType::Swap(other);
    }

    void Reserve(int size) 
    { 
        if (m_Size < size)
        {
            Resize(size);
        }
    }

    const DataType& operator[](int i) const
    { 
        VectorAssert(m_Size > i);
        return *Data(i);
    }

    DataType& operator[](int i)
    {
        VectorAssert(m_Size > i);
        return *Data(i);
    }

    const DataType& operator()(int i) const
    {
        VectorAssert(m_Size > i);
        return *Data(i);
    }

    DataType& operator()(int i)
    {
        VectorAssert(m_Size > i);
        return *Data(i);
    }

    Vector<SharedAllocator<DataType>> operator()(const Range& range) const
    {
        return Vector<SharedAllocator<DataType>>(const_cast<DataType*>(Data(range.First())), range.Count(m_Size - 1));
    }

    Vector<SharedAllocator<DataType>> operator()(const Range& range)
    {
        return Vector<SharedAllocator<DataType>>(const_cast<DataType*>(Data(range.First())), range.Count(m_Size - 1));
    }

    VectorCommaAssignment<AllocatorType> operator=(const DataType& value)
    {
        if (m_Size > 0)
        {
            *Data() = value;
        }

        return VectorCommaAssignment<AllocatorType>(this, 1, value);
    }

    Vector& operator=(const Vector& other);
    template <typename AllocaterType1>
    Vector& operator=(const Vector<AllocaterType1>& other);
    template <typename VectorType1, typename VectorType2, typename OprType>
    Vector& operator=(const Vec2Expr<VectorType1, VectorType2, OprType>& vov);

    Vector& operator+=(const DataType& v1)
    {
        DataType* v2 = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v2[i] += v1;
        }
        return *this;
    }
    
    template <typename AllocatorType> 
    Vector& operator+=(const Vector<AllocatorType>& other)
    {
        assert(m_Size == other.m_Size);
        const DataType* v1 = other.Data();
        DataType* v2 = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v2[i] += v1[i];
        }

        return *this;
    }

    template <typename VectorType1, typename VectorType2, typename OprType>
    Vector& operator+=(const Vec2Expr<VectorType1, VectorType2, OprType>& vov)
    {
        DataType* v = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v[i] += vov[i];
        }

        return *this;
    }

    Vector& operator-=(const DataType& v1)
    {
        DataType* v2 = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v2[i] -= v1;
        }
        return *this;
    }

    template <typename AllocatorType>
    Vector& operator-=(const Vector<AllocatorType>& other)
    {
        assert(m_Size == other.m_Size);
        const DataType* v1 = other.Data();
        DataType* v2 = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v2[i] -= v1[i];
        }

        return *this;
    }

    template <typename VectorType1, typename VectorType2, typename OprType>
    Vector& operator-=(const Vec2Expr<VectorType1, VectorType2, OprType>& vov)
    {
        DataType* v = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v[i] -= vov[i];
        }

        return *this;
    }

    Vector& operator*=(const DataType& v1)
    {
        DataType* v2 = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v2[i] *= v1;
        }
        return *this;
    }

    template <typename AllocatorType>
    Vector& operator*=(const Vector<AllocatorType>& other)
    {
        assert(m_Size == other.m_Size);
        const DataType* v1 = other.Data();
        DataType* v2 = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v2[i] *= v1[i];
        }

        return *this;
    }

    template <typename VectorType1, typename VectorType2, typename OprType>
    Vector& operator*=(const Vec2Expr<VectorType1, VectorType2, OprType>& vov)
    {
        DataType* v = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v[i] *= vov[i];
        }

        return *this;
    }

    Vector& operator/=(const DataType& v1)
    {
        DataType* v2 = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v2[i] /= v1;
        }
        return *this;
    }

    template <typename AllocatorType>
    Vector& operator/=(const Vector<AllocatorType>& other)
    {
        assert(m_Size == other.m_Size);
        const DataType* v1 = other.Data();
        DataType* v2 = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v2[i] /= v1[i];
        }

        return *this;
    }

    template <typename VectorType1, typename VectorType2, typename OprType>
    Vector& operator/=(const Vec2Expr<VectorType1, VectorType2, OprType>& vov)
    {
        DataType* v = Data();
        for (int i = 0; i < m_Size; i++)
        {
            v[i] /= vov[i];
        }

        return *this;
    }
};

