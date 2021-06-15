#pragma once


class ResultOutput
{
public:
    ResultOutput() {}
    virtual ~ResultOutput() {}
};

class CalculiXResultOutput : public ResultOutput
{
public:
    CalculiXResultOutput() {}
    virtual ~CalculiXResultOutput() {}
};
