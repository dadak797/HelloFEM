#pragma once


template<typename AllocatorType /*= DynamicAllocator<double>*/>
class Vector : public AllocatorType {
private:
    int m_Size;

    template<typename AllocatorType1>
    void CopyVector(const Vector<AllocatorType1>& vec);
};

template<typename AllocatorType>
template<typename AllocatorType1>
void Vector<AllocatorType>::CopyVector(const Vector<AllocatorType1>& vec)
{

}