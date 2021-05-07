#include "CmdLineArgumentParser.h"
#include "Common/ErrorHandler.h"
#include "Common/UtilityFunctions.h"

#include <algorithm>


CmdLineArgumentParser::CmdLineArgumentParser(int argc, char** argv)
{
    ProcessCmdLineArguments(argc, argv);
}

void CmdLineArgumentParser::ProcessCmdLineArguments(int argc, char** argv)
{
    int nfa = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strlen(argv[i]) == 2)
            {
                if (i + 1 < argc)
                {
                    i += ProcessOptions(argv[i][1], argv[i + 1]);
                }
                else
                {
                    i += ProcessOptions(argv[i][1], nullptr);
                }
            }
            else
            {
                throw Error::GeneralError("Invalid command line option");
            }
        }
        else
        {
            if (nfa == 0)
            {
                m_InpFn = argv[i];
            }
            else if (nfa == 1)
            {
                m_OutFn = argv[i];
            }
            nfa++;  // ignore else
        }
    }

    if (nfa == 0)
    {
        std::cout << "Input File Name: ";
        std::cin >> m_InpFn;
    }

    if (m_InpType == "")
    {
        std::string ext;
        ext = GetExtension(m_InpFn);
        if (ext == "inp")
        {
            m_InpType = "abq";
        }
        else  // Default Input Type
        {
            m_InpType = "abq";
        }
    }

    if (m_OutType == "")
    {
        m_OutType = "clx";
    }

    if (nfa < 2)
    {
        m_OutFn = CutOffExtension(m_InpFn) + "." + m_OutType;
    }
}

int CmdLineArgumentParser::ProcessOptions(char option, char* argv)
{
    int i = 0, nt = 1;
    if (option != 'h' && (argv == NULL || argv[0] == '-'))
    {
        option = 0;  // Wrong Command Line Format
    }

    switch (option) {
    case 'p':  // Set Number of Threads
        nt = std::max(1, atoi(argv));
        i++;
        break;
    //case 'g':  // Set 'useGPU' Flag
    //    if (argv[0] == 'y') {
    //        if (!CheckGPU()) Error::GeneralError("GPU acceleration is not supported");
    //    }
    //    i++;
    //    break;
    case 's':  // Select Linear Equation Solver
        m_SolverType = argv;
        i++;
        break;
    case 'i': // set input format
        m_InpType = argv;
        if (m_InpType != "abq")
        {
            throw Error::GeneralError("Invalid input file type specified on command line option");
        }            
        i++;
        break;
    case 'o': // set output format
        m_OutType = argv;
        if (m_OutType != "clx")
            throw Error::GeneralError("Invalid output file type specified on command line option");
        i++;
        break;
    case 'h': // print help screen
        PrintCmdHelp();
        break;
    default:
        PrintCmdHelp();
        throw Error::GeneralError("Invalid command line option");
    };

    // Set Number of Threads
    //BLAS_Interface::set_num_threads(nt);
    return i;
}

void CmdLineArgumentParser::PrintCmdHelp()
{
    std::cout << "Usage : HelloFEM inputfile [outputfile] [options]\n";
    std::cout << "  <options>\n";
    std::cout << "  -p nt : set number of threads\n";
    std::cout << "  -g yes/no : use GPU acceleration or not\n";
    std::cout << "  -i abq : input format option. abq=[ABAQUS input]";
    std::cout << "  -o clx : output format option. clx=[CalculiX output]";
    std::cout << "  -s sparse/dense/mfs/amg : select equation solver type\n\n";
}