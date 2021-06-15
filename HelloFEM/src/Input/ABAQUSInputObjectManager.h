#pragma once

#include "AnalysisObjectManager.h"
//#include "MaterialProperty.h"
//#include "Load.h"

//#define GET_MAT_PROPERTY(ptype) \
//        template<typename Mattype> \
//        Mattype* get_##ptype##_property(void){ \
//        if(!has_##ptype##_property()){ \
//        Mattype mpt; \
//        Mattype* mtp = mpt.new_obj(true); \
//        set_##ptype##_property_ptr(mtp); \
//        return mtp;} \
//        else{return get_##ptype##_property_<Mattype>();}} \

inline bool IsStrAllNumber(std::string& str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]) && str[i] != '.') return false;
    }

    return true;
}

template <typename ObjType>
class ABAQUSObject
{
private:
    using StrObjMap = std::unordered_map<std::string, ObjType*>;
    using ObjIterator = typename StrObjMap::iterator;  // typename is necessary
    
    StrObjMap m_ObjMap;

    //void ForEachValue(void(ObjType::*func)(void));
    //void ForEachValue(std::function<void()> func);

public:
    ~ABAQUSObject()
    {
        Clear();
    }

    ObjIterator Begin() { return m_ObjMap.begin(); }
    ObjIterator End() { return m_ObjMap.end(); }
    ObjType& LookUp(std::string name);
    ObjType& Insert(std::string name);
    void Clear();
};

template <typename ObjType>
void ABAQUSObject<ObjType>::Clear()
{
    //if (typeid(ObjType) != typeid(ABAQUSMaterialProperty))
    //{
    for (auto& kv : m_ObjMap)
    {
        delete kv.second;
        kv.second = nullptr;
    }
    //}
    m_ObjMap.clear();
}

template <typename ObjType>
ObjType& ABAQUSObject<ObjType>::LookUp(std::string name)
{
    ObjIterator it = m_ObjMap.find(name);
    if (it != m_ObjMap.end())
    {
        return *(it->second);
    }
    else
    {
        throw Error::InvalidObjectID(name);
    }        
}

template<typename ObjType>
ObjType& ABAQUSObject<ObjType>::Insert(std::string name)
{
    if (IsStrAllNumber(name))
        throw Error::InputError(name);

    ObjIterator it = m_ObjMap.find(name);
    if (it != m_ObjMap.end())
    {
        throw Error::DuplicatedObjectID(name, typeid(ObjType).name());
    }

    ObjType* pObj = new ObjType;
    m_ObjMap[name] = pObj;
    return *pObj;
}
