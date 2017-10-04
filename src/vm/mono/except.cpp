#include "common.h"
#include "mono.h"

MonoException * mono_exception_from_name_msg (MonoImage *image, const char *name_space, const char *name, const char *msg)
{
    CONTRACTL{
        THROWS;
        GC_TRIGGERS;
        MODE_COOPERATIVE;
    } CONTRACTL_END;

    struct _gc {
        EXCEPTIONREF pNewException;
        STRINGREF pMessage;
    } gc;
    ZeroMemory(&gc, sizeof(gc));
    GCPROTECT_BEGIN(gc);

    auto assembly = GetAppDomain()->FindAssembly(image);
    auto exceptClass = ClassLoader::LoadTypeByNameThrowing(assembly->GetAssembly(), name_space, name).GetMethodTable();
    auto ctor = MemberLoader::FindConstructor(exceptClass, &gsig_IM_Str_RetVoid);
    
    gc.pNewException = AllocateObject(exceptClass);
    gc.pMessage = StringObject::NewString(msg);
    MethodDescCallSite invoker(ctor, &gc.pNewException);
    ARG_SLOT args[] = {
        ObjToArgSlot(gc.pNewException),
        ObjToArgSlot(gc.pMessage)
    };
    invoker.Call(args);

    GCPROTECT_END();
    return OBJECTREFToObject(gc.pNewException);
}

MonoException * mono_exception_from_name_two_strings (MonoImage *image, const char *name_space, MonoString *a1, MonoString *a2)
{
    assert(!"mono_exception_from_name_two_strings");
    throw;
}
MonoException* mono_get_exception_argument_null (const char *arg)
{
    assert(!"mono_get_exception_argument_null");
    throw;
}

void DECLSPEC_NORETURN mono_raise_exception (MonoException *ex)
{
    FCALL_CONTRACT;

    COMPlusThrow(ObjectToOBJECTREF(ex));
}

MonoClass* mono_get_exception_class (void)
{
    assert(!"mono_get_exception_class");
    throw;
}
