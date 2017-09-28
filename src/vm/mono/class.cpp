#include "common.h"
#include "mono.h"
#include <algorithm>
#include <vector>

int mono_class_get_userdata_offset()
{
    return offsetof(EEClass, m_userData);
}

MonoClass * mono_class_from_name(MonoImage *image, const char* name_space, const char *name)
{
    auto assembly = GetAppDomain()->FindAssembly(image);
    if (!assembly) return nullptr;
#if _DEBUG
    logger << "Load class:" << name_space << "::" << name << std::endl;
#endif

    return ClassLoader::LoadTypeByNameThrowing(assembly->GetAssembly(), name_space, name).GetMethodTable();
}

MonoMethod* mono_class_get_methods(MonoClass* klass, gpointer *iter)
{
    MethodTable::MethodIterator it(klass);
    if (it.MoveTo(reinterpret_cast<UINT32>(*iter)))
    {
        *iter = reinterpret_cast<gpointer>(it.GetSlotNumber() + 1);
        return it.GetMethodDesc();
    }
    return nullptr;
}

const char* mono_method_get_name(MonoMethod *method)
{
    return method->GetName();
}

gboolean unity_mono_method_is_inflated(MonoMethod* method)
{
    return method->GetClassification() == mcInstantiated;
}

gboolean unity_mono_method_is_generic(MonoMethod* method)
{
    return method->IsGenericMethodDefinition();
}

MonoMethodSignature* mono_method_signature(MonoMethod *m)
{
    return m;
}

gboolean mono_signature_is_instance(MonoMethodSignature *sig)
{
    MetaSig metaSig(sig);
    return metaSig.HasThis();
}

MonoObject* mono_runtime_invoke(MonoMethod *method, void *obj, void **params, MonoObject **exc)
{
    CONTRACTL
    {
        NOTHROW;
        GC_TRIGGERS;
        MODE_ANY;
    }
    CONTRACTL_END;
#if _DEBUG
    logger << "Invoke:" << method->m_pszDebugClassName << "::" << method->m_pszDebugMethodSignature << std::endl;
#endif

    MonoObject* ret = nullptr;
    EX_TRY
    {
        GCX_COOP();
        MethodDescCallSite invoker(method);
        ArgIterator argIt(invoker.GetMetaSig());
        std::vector<ARG_SLOT> args;
        if (argIt.HasThis())
            args.emplace_back(PtrToArgSlot(obj));

        uintptr_t retBuf = 0;
        if (argIt.HasRetBuffArg())
            args.emplace_back(PtrToArgSlot(&retBuf));

        DWORD arg = 0;
        int ofs;
        for (; TransitionBlock::InvalidOffset != (ofs = argIt.GetNextOffset()); arg++)
        {
            UINT32 stackSize = argIt.GetArgSize();
            switch (stackSize)
            {
            case 1:
                args.emplace_back((ARG_SLOT)*reinterpret_cast<BYTE*>(params[arg]));
                break;
            case 2:
                args.emplace_back((ARG_SLOT)*reinterpret_cast<UINT16*>(params[arg]));
                break;
            case 4:
                args.emplace_back((ARG_SLOT)*reinterpret_cast<UINT32*>(params[arg]));
                break;

            case 8:
                switch (argIt.GetArgType())
                {
                case ELEMENT_TYPE_ARRAY:
                case ELEMENT_TYPE_PTR:
                case ELEMENT_TYPE_FNPTR:
                case ELEMENT_TYPE_OBJECT:
                case ELEMENT_TYPE_CLASS:
                case ELEMENT_TYPE_SZARRAY:
                case ELEMENT_TYPE_STRING:
                    args.emplace_back(ObjToArgSlot((OBJECTREF)reinterpret_cast<Object*>(params[arg])));
                    break;
                default:
                    args.emplace_back((ARG_SLOT)*reinterpret_cast<UINT64*>(params[arg]));
                    break;
                }
                break;

            default:
                args.emplace_back(PtrToArgSlot(params[arg]));
            }
        }
        argIt.GetSig()->Reset();
        if (invoker.GetMetaSig()->GetReturnType() == ELEMENT_TYPE_VOID)
            invoker.Call(args.data());
        else
            ret = invoker.Call_RetObjPtr(args.data());
    }
    EX_CATCH
    {
        *exc = OBJECTREFToObject(GET_THROWABLE());
    }
    EX_END_CATCH(RethrowTerminalExceptions);
    return ret;
}

MonoImage* mono_class_get_image(MonoClass *klass)
{
    return klass->GetAssembly()->GetDomainAssembly()->GetFile();
}

MonoClass* mono_get_enum_class(void)
{
    return g_pEnumClass;
}

MonoClass * mono_array_class_get(MonoClass *eclass, guint32 rank)
{
    return ClassLoader::LoadArrayTypeThrowing(eclass, ELEMENT_TYPE_SZARRAY, rank).GetMethodTable();
}

gboolean mono_class_is_subclass_of(MonoClass *klass, MonoClass *klassc, gboolean check_interfaces)
{
    assert(!"mono_class_is_subclass_of");
    throw;
}
