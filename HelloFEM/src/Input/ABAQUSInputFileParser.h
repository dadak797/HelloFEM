#pragma once
#include "InputFileParser.h"
#include "ABAQUSInputModule.h"


class ABAQUSConstants
{
private:
    double m_AbsoluteZero;
    std::vector<std::string> m_NodalTemperature;

public:
    ABAQUSConstants()
        : m_AbsoluteZero(0.0)
    {
    }

    void SetAbsTemperature(double temperature) { m_AbsoluteZero = temperature; }
    double GetAbsTemperature() const { return m_AbsoluteZero; }
    void ExistNodalTemperature(std::string nID)
    {
        auto it = std::find(m_NodalTemperature.begin(), m_NodalTemperature.end(), nID);
        if (it != m_NodalTemperature.end())
        {
            throw Error::InputError("Nodal temperature is already defined in : " + nID);
        }
        else
        {
            m_NodalTemperature.push_back(nID);
        }
    }
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

    std::vector<std::string> m_TKeyword;
    std::vector<std::string> m_TData;
    std::vector<bool> m_IsKeyVal;

    ABAQUSConstants m_AbqConstants;
    ABAQUSModelModule m_AbqModel;

public:
    ABAQUSInputFileParser(const std::string& fin)
        : InputFileParser(fin)
    {

    }

    void ReadInput(AnalysisObjectManager& anaObjMgr, ResultOutput* pResOut) override {}
};

