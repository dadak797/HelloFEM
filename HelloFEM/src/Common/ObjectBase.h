#pragma once


class ObjectBase
{
private:
    int m_ID;

public:
    ObjectBase(int ID = 0): m_ID(ID) {}
    virtual ~ObjectBase() {}

    virtual ObjectBase* CreateNewObj(bool copyFlag = true) = 0;
    virtual int OrgID() const { return m_ID; }

    void SetID(int ID) { m_ID = ID; }
    int GetID() const { return m_ID; }
};


class IDState
{
private:
    enum { USE_NUM_ID, ID_CONVERT, USE_PTR_ID };
    static int m_State;
    friend union IDObj;
};


union IDObj
{
private:
    int m_IDNum;
    ObjectBase* m_IDPtr;

public:
    IDObj() : m_IDNum(0) {}

    IDObj& operator=(int num) {}
};