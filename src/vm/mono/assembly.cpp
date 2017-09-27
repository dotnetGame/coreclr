#include "common.h"
#include "mono.h"

MonoAssembly * mono_assembly_load_from_full(MonoImage *image, const char*fname, MonoImageOpenStatus *status, gboolean refonly)
{
    // Set the caller's assembly to be mscorlib
    DomainAssembly *pCallersAssembly = nullptr;
    PEAssembly *pParentAssembly = nullptr;
    ICLRPrivBinder* pBinderContext = nullptr;

    // Initialize the AssemblySpec
    AssemblySpec spec;
    spec.InitializeSpec(TokenFromRid(1, mdtAssembly), image->GetILimage()->GetMDImport(), pCallersAssembly);
    spec.SetBindingContext(pBinderContext);

    PTR_AppDomain pCurDomain = GetAppDomain();
    DomainAssembly *pDomainAssembly = pCurDomain->LoadDomainAssembly(&spec, image, FILE_LOADED);
    return pDomainAssembly->GetAssembly();
}

MonoImage* mono_assembly_get_image(MonoAssembly *assembly)
{
    return assembly->GetDomainAssembly()->GetFile();
}
