#include "common.h"
#include "mono.h"
#include <algorithm>

int mono_class_get_userdata_offset ()
{
    return offsetof(EEClass, m_userData);
}

MonoClass * mono_class_from_name (MonoImage *image, const char* name_space, const char *name)
{
    auto assembly = GetAppDomain()->FindAssembly(image);
    if (!assembly) return nullptr;
#if _DEBUG
    logger << "Load class:" << name_space << "::" << name << std::endl;
#endif
    return ClassLoader::LoadTypeByNameThrowing(assembly->GetAssembly(), name_space, name).GetMethodTable()->GetClass();
}
