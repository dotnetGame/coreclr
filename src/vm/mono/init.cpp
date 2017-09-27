#include "common.h"
#include "mono.h"
#include <string>
#include <memory>

PathString s_assemblyDir;
PathString s_configDir;

void mono_set_dirs(const char *assembly_dir, const char *config_dir)
{
    s_assemblyDir.SetANSI(assembly_dir); if (!s_assemblyDir.EndsWith(L'\\'))s_assemblyDir.Append(L'\\');
    s_configDir.SetANSI(config_dir); if (!s_configDir.EndsWith(L'\\'))s_configDir.Append(L'\\');

#if _DEBUG
    wlogger << L"assebmly dir: " << s_assemblyDir.GetUnicode() << std::endl;
    wlogger << L"config dir: " << s_configDir.GetUnicode() << std::endl;
#endif
}

std::string s_assemblyPath;

void mono_set_assemblies_path(const char* path)
{
    s_assemblyPath = path;
#if _DEBUG
    logger << "assebmly path: " << path << std::endl;
#endif
}

void mono_config_parse(const char *filename)
{
#if _DEBUG
    logger << "[TODO] parsing config: " << std::endl;
#endif
}

bool s_restoreSignalChaining = false;

void mono_set_signal_chaining(gboolean chain_signals)
{
    s_restoreSignalChaining = chain_signals != 0;
}


/* optimization flags */
#define OPTFLAG(id,shift,name,descr) MONO_OPT_ ## id = 1 << shift,
enum {
#include "optflags-def.h"
    MONO_OPT_LAST
};

#define DEFAULT_OPTIMIZATIONS (	\
	MONO_OPT_PEEPHOLE |	\
	MONO_OPT_CFOLD |	\
	MONO_OPT_INLINE |       \
	MONO_OPT_CONSPROP |     \
	MONO_OPT_COPYPROP |     \
	MONO_OPT_TREEPROP |     \
	MONO_OPT_DEADCE |       \
	MONO_OPT_BRANCH |	\
	MONO_OPT_LINEARS |	\
	MONO_OPT_INTRINS |  \
	MONO_OPT_LOOP |  \
	MONO_OPT_EXCEPTION |  \
    MONO_OPT_CMOV |  \
	MONO_OPT_GSHARED |	\
	MONO_OPT_SIMD |	\
	MONO_OPT_AOT)

#define EXCLUDED_FROM_ALL (MONO_OPT_SHARED | MONO_OPT_PRECOMP)

int mono_parse_default_optimizations(const char* p)
{
    return DEFAULT_OPTIMIZATIONS;
}

int s_verboseLevel = 0;
guint32 s_opts = DEFAULT_OPTIMIZATIONS;

void mono_set_defaults(int verbose_level, guint32 opts)
{
    s_verboseLevel = verbose_level;
    s_opts = opts;
}

void mono_unity_runtime_set_main_args(int argc, const char* argv[])
{
#if _DEBUG
    logger << "command line: ";
    for (int i = 0; i < argc; i++)
        logger << argv[i] << ' ';
    logger << std::endl;
#endif
}

MonoDomain* mono_jit_init(const char *file)
{
#if _DEBUG
    logger << "jit init: " << file << std::endl;
#endif
    return nullptr;
}

// Utility macro for testing whether or not a flag is set.
#define HAS_FLAG(value, flag) (((value) & (flag)) == (flag))

// Environment variable for setting whether or not to use Server GC.
// Off by default.
static const wchar_t *serverGcVar = W("CORECLR_SERVER_GC");

// Environment variable for setting whether or not to use Concurrent GC.
// On by default.
static const wchar_t *concurrentGcVar = W("CORECLR_CONCURRENT_GC");

// The name of the CoreCLR native runtime DLL.
static const wchar_t *coreCLRDll = W("CoreCLR.dll");

// The location where CoreCLR is expected to be installed. If CoreCLR.dll isn't
//  found in the same directory as the host, it will be looked for here.
static const wchar_t *coreCLRInstallDirectory = W("%windir%\\system32\\");

// Encapsulates the environment that CoreCLR will run in, including the TPALIST
class HostEnvironment
{
    // The path to this module
    PathString m_hostPath;

    // The path to the directory containing this module
    PathString m_hostDirectoryPath;

    // The name of this module, without the path
    const wchar_t *m_hostExeName;

    // The list of paths to the assemblies that will be trusted by CoreCLR
    SString m_tpaList;

    ICLRRuntimeHost4* m_CLRRuntimeHost;

    HMODULE m_coreCLRModule;


    // Attempts to load CoreCLR.dll from the given directory.
    // On success pins the dll, sets m_coreCLRDirectoryPath and returns the HMODULE.
    // On failure returns nullptr.
    HMODULE TryLoadCoreCLR(const wchar_t* directoryPath) {
        return GetModuleHandleW(coreCLRDll);
    }

public:
    // The path to the directory that CoreCLR is in
    PathString m_coreCLRDirectoryPath;

    HostEnvironment()
        : m_CLRRuntimeHost(nullptr) {

        // Discover the path to this exe's module. All other files are expected to be in the same directory.
        WszGetModuleFileName(::GetModuleHandleW(nullptr), m_hostPath);

        // Search for the last backslash in the host path.
        SString::CIterator lastBackslash = m_hostPath.End();
        m_hostPath.FindBack(lastBackslash, W('\\'));

        // Copy the directory path
        m_hostDirectoryPath.Set(m_hostPath, m_hostPath.Begin(), lastBackslash + 1);

        // Save the exe name
        m_hostExeName = m_hostPath.GetUnicode(lastBackslash + 1);

        wlogger << W("Host directory: ") << m_hostDirectoryPath.GetUnicode() << std::endl;

        // Check for %CORE_ROOT% and try to load CoreCLR.dll from it if it is set
        StackSString coreRoot;
        m_coreCLRModule = NULL; // Initialize this here since we don't call TryLoadCoreCLR if CORE_ROOT is unset.
        if (WszGetEnvironmentVariable(W("CORE_ROOT"), coreRoot) > 0 && coreRoot.GetCount() > 0)
        {
            coreRoot.Append(W('\\'));
            m_coreCLRModule = TryLoadCoreCLR(coreRoot);
        }
        else
        {
            wlogger << W("CORE_ROOT not set; skipping") << std::endl;
            wlogger << W("You can set the environment variable CORE_ROOT to point to the path") << std::endl;
            wlogger << W("where CoreCLR.dll lives to help CoreRun.exe find it.") << std::endl;
        }

        // Try to load CoreCLR from the directory that coreRun is in
        if (!m_coreCLRModule) {
            m_coreCLRModule = TryLoadCoreCLR(m_hostDirectoryPath);
        }

        if (!m_coreCLRModule) {

            // Failed to load. Try to load from the well-known location.
            wchar_t coreCLRInstallPath[MAX_LONGPATH];
            ::ExpandEnvironmentStringsW(coreCLRInstallDirectory, coreCLRInstallPath, MAX_LONGPATH);
            m_coreCLRModule = TryLoadCoreCLR(coreCLRInstallPath);

        }

        if (m_coreCLRModule) {

            // Save the directory that CoreCLR was found in
            DWORD modulePathLength = WszGetModuleFileName(m_coreCLRModule, m_coreCLRDirectoryPath);

            // Search for the last backslash and terminate it there to keep just the directory path with trailing slash
            SString::Iterator lastBackslash = m_coreCLRDirectoryPath.End();
            m_coreCLRDirectoryPath.FindBack(lastBackslash, W('\\'));
            m_coreCLRDirectoryPath.Truncate(lastBackslash + 1);

        }
        else {
            wlogger << W("Unable to load ") << coreCLRDll << std::endl;
        }
    }

    ~HostEnvironment() {
        if (m_coreCLRModule) {
            // Free the module. This is done for completeness, but in fact CoreCLR.dll 
            // was pinned earlier so this call won't actually free it. The pinning is
            // done because CoreCLR does not support unloading.
            ::FreeLibrary(m_coreCLRModule);
        }
    }

    bool TPAListContainsFile(_In_z_ wchar_t* fileNameWithoutExtension, _In_reads_(countExtensions) const wchar_t** rgTPAExtensions, int countExtensions)
    {
        if (m_tpaList.IsEmpty()) return false;

        for (int iExtension = 0; iExtension < countExtensions; iExtension++)
        {
            StackSString fileName;
            fileName.Append(W("\\")); // So that we don't match other files that end with the current file name
            fileName.Append(fileNameWithoutExtension);
            fileName.Append(rgTPAExtensions[iExtension] + 1);
            fileName.Append(W(";")); // So that we don't match other files that begin with the current file name

            if (m_tpaList.Find(m_tpaList.Begin(), fileName))
            {
                return true;
            }
        }
        return false;
    }

    void RemoveExtensionAndNi(_In_z_ wchar_t* fileName)
    {
        // Remove extension, if it exists
        wchar_t* extension = wcsrchr(fileName, W('.'));
        if (extension != NULL)
        {
            extension[0] = W('\0');

            // Check for .ni
            size_t len = wcslen(fileName);
            if (len > 3 &&
                fileName[len - 1] == W('i') &&
                fileName[len - 2] == W('n') &&
                fileName[len - 3] == W('.'))
            {
                fileName[len - 3] = W('\0');
            }
        }
    }

    void AddFilesFromDirectoryToTPAList(_In_z_ const wchar_t* targetPath, _In_reads_(countExtensions) const wchar_t** rgTPAExtensions, int countExtensions)
    {
        wlogger << W("Adding assemblies from ") << targetPath << W(" to the TPA list") << std::endl;
        StackSString assemblyPath;
        const size_t dirLength = wcslen(targetPath);

        for (int iExtension = 0; iExtension < countExtensions; iExtension++)
        {
            assemblyPath.Set(targetPath, (DWORD)dirLength);
            assemblyPath.Append(rgTPAExtensions[iExtension]);
            WIN32_FIND_DATA data;
            HANDLE findHandle = WszFindFirstFile(assemblyPath, &data);

            if (findHandle != INVALID_HANDLE_VALUE) {
                do {
                    if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                        // It seems that CoreCLR doesn't always use the first instance of an assembly on the TPA list (ni's may be preferred
                        // over il, even if they appear later). So, only include the first instance of a simple assembly name to allow
                        // users the opportunity to override Framework assemblies by placing dlls in %CORE_LIBRARIES%

                        // ToLower for case-insensitive comparisons
                        wchar_t* fileNameChar = data.cFileName;
                        while (*fileNameChar)
                        {
                            *fileNameChar = towlower(*fileNameChar);
                            fileNameChar++;
                        }

                        // Remove extension
                        wchar_t fileNameWithoutExtension[MAX_PATH_FNAME];
                        wcscpy_s(fileNameWithoutExtension, MAX_PATH_FNAME, data.cFileName);

                        RemoveExtensionAndNi(fileNameWithoutExtension);

                        // Add to the list if not already on it
                        if (!TPAListContainsFile(fileNameWithoutExtension, rgTPAExtensions, countExtensions))
                        {
                            assemblyPath.Truncate(assemblyPath.Begin() + (DWORD)dirLength);
                            assemblyPath.Append(data.cFileName);
                            m_tpaList.Append(assemblyPath);
                            m_tpaList.Append(W(';'));
                        }
                        else
                        {
                            wlogger << W("Not adding ") << targetPath << data.cFileName << W(" to the TPA list because another file with the same name is already present on the list") << std::endl;
                        }
                    }
                } while (0 != WszFindNextFile(findHandle, &data));

                FindClose(findHandle);
            }
        }
    }

    // Returns the semicolon-separated list of paths to runtime dlls that are considered trusted.
    // On first call, scans the coreclr directory for dlls and adds them all to the list.
    const wchar_t * GetTpaList() {
        if (m_tpaList.IsEmpty()) {
            const wchar_t *rgTPAExtensions[] = {
                W("*.ni.dll"),		// Probe for .ni.dll first so that it's preferred if ni and il coexist in the same dir
                W("*.dll"),
                W("*.ni.exe"),
                W("*.exe"),
                W("*.ni.winmd")
                W("*.winmd")
            };

            AddFilesFromDirectoryToTPAList(s_assemblyDir.GetUnicode(), rgTPAExtensions, _countof(rgTPAExtensions));
        }

        return m_tpaList;
    }

    // Returns the path to the host module
    const wchar_t * GetHostPath() {
        return m_hostPath;
    }

    // Returns the path to the host module
    const wchar_t * GetHostExeName() {
        return m_hostExeName;
    }

    // Returns the ICLRRuntimeHost4 instance, loading it from CoreCLR.dll if necessary, or nullptr on failure.
    ICLRRuntimeHost4* GetCLRRuntimeHost() {
        if (!m_CLRRuntimeHost) {

            if (!m_coreCLRModule) {
                wlogger << W("Unable to load ") << coreCLRDll << std::endl;
                return nullptr;
            }

            wlogger << W("Finding GetCLRRuntimeHost(...)") << std::endl;

            FnGetCLRRuntimeHost pfnGetCLRRuntimeHost =
                (FnGetCLRRuntimeHost)::GetProcAddress(m_coreCLRModule, "GetCLRRuntimeHost");

            if (!pfnGetCLRRuntimeHost) {
                wlogger << W("Failed to find function GetCLRRuntimeHost in ") << coreCLRDll << std::endl;
                return nullptr;
            }

            wlogger << W("Calling GetCLRRuntimeHost(...)") << std::endl;

            HRESULT hr = pfnGetCLRRuntimeHost(IID_ICLRRuntimeHost4, (IUnknown**)&m_CLRRuntimeHost);
            if (FAILED(hr)) {
                wlogger << W("Failed to get ICLRRuntimeHost4 interface. ERRORCODE: 0x") << std::hex << hr << std::endl;
                return nullptr;
            }
        }

        return m_CLRRuntimeHost;
    }


};

STARTUP_FLAGS CreateStartupFlags() {
    auto initialFlags =
        static_cast<STARTUP_FLAGS>(
            STARTUP_FLAGS::STARTUP_LOADER_OPTIMIZATION_SINGLE_DOMAIN |
            STARTUP_FLAGS::STARTUP_SINGLE_APPDOMAIN |
            STARTUP_FLAGS::STARTUP_CONCURRENT_GC);

    // server GC is off by default, concurrent GC is on by default.
    auto checkVariable = [&](STARTUP_FLAGS flag, const wchar_t *var) {
        wchar_t result[25];
        size_t outsize;
        if (_wgetenv_s(&outsize, result, 25, var) == 0 && outsize > 0) {
            // set the flag if the var is present and set to 1,
            // clear the flag if the var isp resent and set to 0.
            // Otherwise, ignore it.
            if (_wcsicmp(result, W("1")) == 0) {
                initialFlags = static_cast<STARTUP_FLAGS>(initialFlags | flag);
            }
            else if (_wcsicmp(result, W("0")) == 0) {
                initialFlags = static_cast<STARTUP_FLAGS>(initialFlags & ~flag);
            }
        }
    };

    checkVariable(STARTUP_FLAGS::STARTUP_SERVER_GC, serverGcVar);
    checkVariable(STARTUP_FLAGS::STARTUP_CONCURRENT_GC, concurrentGcVar);

    return initialFlags;
}

std::unique_ptr<HostEnvironment> s_hostEnvironment;

MonoDomain* mono_jit_init_version(const char *domain_name, const char *runtime_version)
{
    s_hostEnvironment.reset(new HostEnvironment());

    ICLRRuntimeHost4 *host = s_hostEnvironment->GetCLRRuntimeHost();
    if (!host) return nullptr;

    STARTUP_FLAGS flags = CreateStartupFlags();
    // Default startup flags
    auto hr = host->SetStartupFlags(flags);
    if (FAILED(hr)) {
        wlogger << W("Failed to set startup flags. ERRORCODE: ") << std::hex << hr << std::endl;
        return false;
    }
    wlogger << W("Starting ICLRRuntimeHost4") << std::endl;
    hr = host->Start();
    if (FAILED(hr)) {
        wlogger << W("Failed to start CoreCLR. ERRORCODE: ") << std::hex << hr << std::endl;
        return false;
    }

    StackSString tpaList;
    tpaList.Append(s_hostEnvironment->GetTpaList());

    StackSString nativeDllSearchDirs(s_hostEnvironment->m_coreCLRDirectoryPath);
    const wchar_t *property_keys[] = {
        W("TRUSTED_PLATFORM_ASSEMBLIES"),
        W("NATIVE_DLL_SEARCH_DIRECTORIES")
    };
    const wchar_t *property_values[] = {
        // TRUSTED_PLATFORM_ASSEMBLIES
        tpaList,
        // APP_PATHS
        // NATIVE_DLL_SEARCH_DIRECTORIES
        nativeDllSearchDirs,
    };
    wlogger << W("Creating an AppDomain") << std::endl;
    for (int idx = 0; idx < sizeof(property_keys) / sizeof(wchar_t*); idx++)
    {
        wlogger << property_keys[idx] << W("=") << property_values[idx] << std::endl;
    }

    StackSString domainName;
    domainName.SetANSI(domain_name);
    DWORD domainId;
    hr = host->CreateAppDomainWithManager(
        domainName,                         // The friendly name of the AppDomain
                                            // Flags:
                                            // APPDOMAIN_ENABLE_PLATFORM_SPECIFIC_APPS
                                            // - By default CoreCLR only allows platform neutral assembly to be run. To allow
                                            //   assemblies marked as platform specific, include this flag
                                            //
                                            // APPDOMAIN_ENABLE_PINVOKE_AND_CLASSIC_COMINTEROP
                                            // - Allows sandboxed applications to make P/Invoke calls and use COM interop
                                            //
                                            // APPDOMAIN_SECURITY_SANDBOXED
                                            // - Enables sandboxing. If not set, the app is considered full trust
                                            //
                                            // APPDOMAIN_IGNORE_UNHANDLED_EXCEPTION
                                            // - Prevents the application from being torn down if a managed exception is unhandled
                                            //
        APPDOMAIN_ENABLE_PLATFORM_SPECIFIC_APPS |
        APPDOMAIN_ENABLE_PINVOKE_AND_CLASSIC_COMINTEROP |
        APPDOMAIN_DISABLE_TRANSPARENCY_ENFORCEMENT,
        NULL,                // Name of the assembly that contains the AppDomainManager implementation
        NULL,                    // The AppDomainManager implementation type name
        sizeof(property_keys) / sizeof(wchar_t*),  // The number of properties
        property_keys,
        property_values,
        &domainId);
    if (FAILED(hr)) {
        wlogger << W("Failed call to CreateAppDomainWithManager. ERRORCODE: ") << std::hex << hr << std::endl;
        return false;
    }

    wlogger << W("AppDomain Created. (") << domainName.GetUnicode() << W(")") << std::endl;

#if _DEBUG
    logger << "jit init: domianName:" << domain_name << ", runtimeVersion: " << runtime_version << std::endl;
#endif
    return AppDomain::GetCurrentDomain();
}

void mono_unity_domain_set_config(MonoDomain *domain, const char *base_dir, const char *config_file_name)
{
    // Do nothing
}

SString s_embeddingHostName;

void mono_unity_set_embeddinghostname(const char* name)
{
    s_embeddingHostName.SetANSI(name);
#if _DEBUG
    wlogger << L"Embedding HostName:" << s_embeddingHostName.GetUnicode() << std::endl;
#endif
}

void mono_runtime_unhandled_exception_policy_set(MonoRuntimeUnhandledExceptionPolicy policy)
{
    // Do nothing
}

MonoImage * mono_image_open_from_data_with_name(char *data, guint32 data_len, gboolean need_copy, MonoImageOpenStatus *status, gboolean refonly, const char *name)
{
    PEImageHolder image(PEImage::LoadFlat(data, data_len));
    if (image)
        image->LoadNoFile();
#if _DEBUG
    logger << "open image:" << name << std::endl;
#endif
    ReleaseHolder<ICLRPrivAssembly> pAssembly;
    DWORD dwMessageID = IDS_EE_FILELOAD_ERROR_GENERIC;

    // Set the caller's assembly to be mscorlib
    DomainAssembly *pCallersAssembly = nullptr;
    PEAssembly *pParentAssembly = nullptr;
    ICLRPrivBinder* pBinderContext = nullptr;

    // Initialize the AssemblySpec
    AssemblySpec spec;
    spec.InitializeSpec(TokenFromRid(1, mdtAssembly), image->GetMDImport(), pCallersAssembly);
    spec.SetBindingContext(pBinderContext);

    HRESULT hr = S_OK;
    PTR_AppDomain pCurDomain = GetAppDomain();
    CLRPrivBinderCoreCLR *pTPABinder = pCurDomain->GetTPABinderContext();
    // Bind the assembly using TPA binder
    hr = pTPABinder->BindUsingPEImage(image, false, &pAssembly);

    if (hr != S_OK)
    {
        // Give a more specific message for the case when we found the assembly with the same name already loaded.
        if (hr == COR_E_FILELOAD)
        {
            dwMessageID = IDS_HOST_ASSEMBLY_RESOLVER_ASSEMBLY_ALREADY_LOADED_IN_CONTEXT;
        }

        StackSString name;
        spec.GetFileOrDisplayName(0, name);
        COMPlusThrowHR(COR_E_FILELOAD, dwMessageID, name);
    }

    BINDER_SPACE::Assembly* assem;
    assem = BINDER_SPACE::GetAssemblyFromPrivAssemblyFast(pAssembly);

    auto file = PEAssembly::Open(pParentAssembly, assem->GetPEImage(), assem->GetNativePEImage(), pAssembly, FALSE);

    return file;
}

void mono_image_close(MonoImage *image)
{
    image->Release();
}
