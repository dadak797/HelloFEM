#include "InputFileParser.h"


void InputFileParser::OpenInputFile(const std::string& fin)
{
    m_Fin.open(fin);
}

void InputFileParser::ReadInputFile(AnalysisObjectManager& anaObjMgr, ResultOutput* pResOut)
{
    ReadInput(anaObjMgr, pResOut);
}