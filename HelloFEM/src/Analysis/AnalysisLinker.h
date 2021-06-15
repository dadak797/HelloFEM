#pragma once

#include "Analysis.h"

template<typename Element> class ObjectContainer;
class AnalysisObjectManager;

class AnalysisLinker
{
    using ElementObj = ObjectContainer<Element>;
    using ElementObjSPtr = std::shared_ptr<ElementObj>;

private:
    std::vector<ElementObjSPtr> m_ElementArray;
    AnalysisObjectManager* m_AOM;

};

