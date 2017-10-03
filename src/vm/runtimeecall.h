#ifndef __runtimeecall_h__
#define __runtimeecall_h__

#include "ecall.h"
#include <unordered_map>

class RuntimeECall
{
public:
    static ECFunc* GetECFuncForMethod(MethodDesc *pMD);

    static void RegisterECFunc(const char* name, LPVOID code);

    static std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, ECFunc>>> s_ECClasses;
};

#endif
