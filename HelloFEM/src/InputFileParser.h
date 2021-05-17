#pragma once
#include <fstream>

class AnalysisObjectManager;
class ResultOutput;

class InputFileParser 
{
private:
    std::ifstream m_Fin;

protected:
    std::ifstream& InputFile() { return m_Fin; }

    // virtual member functions
    virtual void ReadInput(AnalysisObjectManager& anaObjMgr, ResultOutput* pResOut) = 0;

public:
    InputFileParser(const std::string& fin) { OpenInputFile(fin); }
    ~InputFileParser() { CloseInputFile(); }

    // non-virtual member functions
    void OpenInputFile(const std::string& fin);
    void CloseInputFile() { m_Fin.close(); }
    void ReadInputFile(AnalysisObjectManager& anaObjMgr, ResultOutput* pResOut);
};

class ABAQUSInputFileParser : public InputFileParser
{
private:
    int m_Dim;
    int m_Level;
    int m_LineNumber;
    bool m_InitKeyword;
    bool m_HyperFlag;
    bool m_IsComp;

public:
    ABAQUSInputFileParser(const std::string& fin)
        : InputFileParser(fin) 
    {

    }

    void ReadInput(AnalysisObjectManager& anaObjMgr, ResultOutput* pResOut) override {}
};