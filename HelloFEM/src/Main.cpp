#include <iostream>
#include "AnalysisObjectManager.h"


int_type IdState::_state = IdState::USE_NUM_ID;

int main(int argc, char** argv)
{
    std::cout << "Structural Analysis Solver - HelloFEM" << std::endl;
    AnalysisObjectManager aom;

    return 0;
}