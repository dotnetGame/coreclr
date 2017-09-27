#include <Windows.h>
#include <string>
#include <Shlwapi.h>

HMODULE h_coreclr = nullptr;

std::wstring thisDllDirPath()
{
    std::wstring thisPath = L"";
    WCHAR path[MAX_PATH];
    HMODULE hm;
    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPWSTR)&thisDllDirPath, &hm))
    {
        GetModuleFileName(hm, path, sizeof(path));
        PathRemoveFileSpec(path);
        thisPath = path;
        if (!thisPath.empty() &&
            thisPath.back() != '\\')
            thisPath += L"\\";
    }

    return thisPath;
}

std::wstring coreclrPath;

extern "C" BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        coreclrPath = thisDllDirPath() + L"coreclr.dll";
        h_coreclr = LoadLibrary(coreclrPath.c_str());
        return h_coreclr != nullptr;
    case DLL_PROCESS_DETACH:
        FreeLibrary(h_coreclr);
        h_coreclr = nullptr;
    }
    return TRUE;
}
