#pragma once


#define ASSERT(x) if(!(x)) __debugbreak();


class ErrorHandler {
protected:
    std::string m_Message;

    ErrorHandler() {}
    ErrorHandler(const std::string& str) 
        :m_Message(str) {}

public:
    void HandleError() { std::cerr << m_Message << std::endl; }
};


namespace Error {

    class InvalidObjectID : public ErrorHandler {
    public:
        InvalidObjectID(int ID) { m_Message = std::string("Invalid Object ID ") + std::to_string(ID); }
        InvalidObjectID(std::string ID) { m_Message = std::string("Invalid Object ID ") + ID; }
    };

    class DuplicatedObjectID : public ErrorHandler {
    public:
        DuplicatedObjectID(int ID, const std::string& objName) { m_Message = std::string("Duplicated Object ID ") + std::to_string(ID) + " in " + objName; }
        DuplicatedObjectID(std::string ID, const std::string& objName) { m_Message = std::string("Duplicated Object ID ") + ID + " in " + objName; }
    };

    class BadShape : public ErrorHandler {
    public:
        BadShape(int ID) { m_Message = std::string("Element ") + std::to_string(ID) + std::string(" has bad shape"); }
    };

    class UnsupportedElementType : public ErrorHandler {
    public:
        UnsupportedElementType(int ID) { m_Message = std::string("Element ") + std::to_string(ID) + std::string(" has unsupported element type"); }
    };

    class SingularMatrix : public ErrorHandler {
    public:
        SingularMatrix(int ID) { m_Message = std::string("Singularity in coefficient matrix ") + std::to_string(ID); }
        SingularMatrix(int ID, const char* msg) { m_Message = std::string(msg) + std::to_string(ID); }
    };

    class InputError : public ErrorHandler {
    public:
        InputError(const std::string& str) 
            :ErrorHandler(str) {}
        InputError(const char* str) 
            :ErrorHandler(str) {}
        InputError(const char* obj, const std::string& ID) { m_Message = std::string("Error in ") + obj + " " + ID; }
        InputError(int line, const char* msg)
        {
            std::stringstream ss;
            ss << line;
            m_Message = std::string("Line in ") + ss.str() + " : " + msg;
        }
    };

    class NotConverged : public ErrorHandler {
    public:
        NotConverged(int maxIter) { m_Message = std::string("Failed to converge within ") + std::to_string(maxIter) + " iterations"; }
    };

    class Divergence : public ErrorHandler {
    public:
        Divergence() { m_Message = std::string("Failed to converge"); }
    };

    class GeneralError : public ErrorHandler {
    public:
        GeneralError(const std::string& str) 
            :ErrorHandler(str) {}
    };

}