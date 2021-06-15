#pragma once


class CmdLineArgumentParser
{
public:
    CmdLineArgumentParser(int argc, char** argv);
    const std::string& GetInputFileName() const { return m_InpFn; }
    const std::string& GetOutputFileName() const { return m_OutFn; }
    const std::string& GetInputFileType() const { return m_InpType; }
    const std::string& GetOutputFileType() const { return m_OutType; }
    const std::string& GetSolverType() const { return m_SolverType; }

private:
    std::string m_InpFn, m_OutFn;
    std::string m_InpType, m_OutType;
    std::string m_SolverType;

    void ProcessCmdLineArguments(int argc, char** argv);
    int ProcessOptions(char option, char* argv);
    void PrintCmdHelp();
};

