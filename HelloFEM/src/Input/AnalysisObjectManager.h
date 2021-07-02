#pragma once

#include "AnalysisLinker.h"
#include "Node.h"


template <typename ObjType>
class ObjectContainer
{
private:
    std::list<ObjType*> m_ObjList;

public:
    void Insert(ObjType obj)
    {
        ObjType* pObj = static_cast<ObjType*>(obj.NewObj(true));
        m_ObjList.push_back(pObj);
    }

    void InsertPtr(ObjType* pObj)
    {
        m_ObjList.push_back(pObj);
    }

    std::list<ObjType*> GetObjList() const { return m_ObjList; }

    void DeleteAll()
    {
        for (auto pObj : m_ObjList)
        {
            delete pObj;
            pObj = nullptr;
        }
    }
};

class AnalysisObjectManager
{
private:
    AnalysisLinker m_AnalysisLinker;
    ObjectContainer<Node> m_Nodes;
};
