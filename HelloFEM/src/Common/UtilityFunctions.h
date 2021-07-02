#pragma once


inline std::string GetExtension(const std::string& fn)
{
    size_t l = fn.rfind(".");
    return fn.substr(l + 1, fn.length());
}

inline std::string CutOffExtension(const std::string& fn)
{
    size_t l = fn.rfind(".");
    return fn.substr(0, l);
}