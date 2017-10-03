#include "common.h"
#include "mono.h"

MonoClass* mono_object_get_class(MonoObject *obj)
{
    if (!obj) return nullptr;
    return obj->GetMethodTable();
}

MonoObject *
mono_object_isinst(MonoObject *obj, MonoClass *klass)
{
    assert(!"mono_object_isinst");
    throw;
}

MonoObject *
mono_object_new(MonoDomain *domain, MonoClass *klass)
{
    CONTRACTL
    {
        GC_TRIGGERS;
        THROWS;
        MODE_ANY;
    }
    CONTRACTL_END;

    struct _gc {
        OBJECTREF pNewObject;
    } gc;
    ZeroMemory(&gc, sizeof(gc));
    GCX_COOP();
    GCPROTECT_BEGIN(gc);

    gc.pNewObject = AllocateObject(klass);
    gc.pNewObject->SetAppDomain(domain);

    GCPROTECT_END();
    return OBJECTREFToObject(gc.pNewObject);
}

MonoObject *
mono_object_new_alloc_specific(MonoVTable *vtable)
{
    assert(!"mono_object_new_alloc_specific");
    throw;
}

MonoObject *
mono_object_new_specific(MonoVTable *vtable)
{
    assert(!"mono_object_new_specific");
    throw;
}
