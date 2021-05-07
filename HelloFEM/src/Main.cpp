#include "AnalysisObjectManager.h"
#include "Common/ObjectBase.h"
#include "CmdLineArgumentParser.h"
#include "ResultOutput.h"
#include "InputFileParser.h"


int IDState::s_State = IDState::USE_NUM_ID;

int main(int argc, char** argv)
{
    std::cout << "Structural Analysis Solver - HelloFEM" << std::endl;
    
    AnalysisObjectManager anaObjMgr;

    {
        CmdLineArgumentParser clap(argc, argv);
        std::cout << "Reading input file \"" << clap.GetInputFileName() << "\"" << std::endl;
        
        ResultOutput* pResOut = nullptr;
        if (clap.GetOutputFileType() == "clx")
        {
            pResOut = new CalculiXResultOutput;
        }        

        if (clap.GetInputFileType() == "abq")
        {
            ABAQUSInputFileParser ifp(clap.GetInputFileName());
            ifp.ReadInput(anaObjMgr, pResOut);
        }
    }

    return 0;
}