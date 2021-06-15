#pragma once

#include "ErrorHandler.h"


class ObjectBase
{
private:
    int m_ID;

public:
    ObjectBase(int ID = 0): m_ID(ID) {}
    virtual ~ObjectBase() {}

    virtual ObjectBase* NewObj(bool copyFlag = true) = 0;
    virtual int OrgID() const { return m_ID; }  // Mapping ID to original ID

    void SetID(int ID) { m_ID = ID; }
    int GetID() const { return m_ID; }
};


class IDState  // How about change to Singleton?
{
private:
    enum { USE_NUM_ID, ID_CONVERT, USE_PTR_ID };
    static int s_State;
    friend union IDObj;
};


union IDObj  // How about change union to class?
{
private:
    int m_IDNum;
    ObjectBase* m_IDPtr;

public:
    IDObj() : m_IDNum(0) {}

    bool IsNull() const { return m_IDNum == 0; }

    IDObj& operator=(const int num) 
    {
        ASSERT(IDState::s_State == IDState::USE_NUM_ID); 
        m_IDNum = num;
        return *this;
    }

    IDObj& operator=(ObjectBase* ptr)
    {
        ASSERT(IDState::s_State == IDState::ID_CONVERT || IDState::s_State == IDState::USE_PTR_ID);
        m_IDPtr = ptr;
        return *this;
    }

    int GetIDNum() const
    {
        if (IDState::s_State == IDState::USE_NUM_ID || IDState::s_State == IDState::ID_CONVERT)
        {
            return m_IDNum;
        }

        return m_IDPtr->GetID();
    }

    template <typename ObjType>
    ObjType& GetObj()
    {
        ASSERT(IDState::s_State == IDState::USE_PTR_ID);
        return *static_cast<ObjType*>(m_IDPtr);
    }

    template <typename ObjType>
    const ObjType& GetObj()
    {
        ASSERT(IDState::s_State == IDState::USE_PTR_ID);
        return *static_cast<const ObjType*>(m_IDPtr);
    }

    template <typename MapType>
    void ConvertID2Ptr(MapType& objMap)
    {
        ASSERT(IDState::s_State == IDState::ID_CONVERT);
        if (IsNull())
        {
            return;
        }

        typename::MapType::iterator it = objMap.find(m_IDNum);
        if (it == objMap.end())
        {
            throw Error::InvalidObjectID(m_IDNum);
        }
        
        m_IDPtr = static_cast<ObjectBase*>(it->second);
    }

    static void InitIDState() { IDState::s_State = IDState::USE_NUM_ID; }
    static void BeginPtrLink() { IDState::s_State = IDState::ID_CONVERT; }
    static void EndPtrLine() { IDState::s_State = IDState::USE_PTR_ID; }
};