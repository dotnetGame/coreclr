#include "common.h"
#include "mono.h"
#include <algorithm>
#include <vector>

int mono_class_get_userdata_offset()
{
    return offsetof(MonoClass, m_userData);
}

MonoClass * mono_class_from_name(MonoImage *image, const char* name_space, const char *name)
{
    MonoClass* klass = nullptr;
    EX_TRY
    {
        auto assembly = GetAppDomain()->FindAssembly(image);
        if (assembly)
        {
#if _DEBUG
            logger << "Load class:" << name_space << "::" << name << std::endl;
#endif

            klass = ClassLoader::LoadTypeByNameThrowing(assembly->GetAssembly(), name_space, name).GetMethodTable();
        }
    }
    EX_CATCH
    {
        SString ex;
        GET_EXCEPTION()->GetMessage(ex);
        SString ex2;
        ex.ConvertToUTF8(ex2);
#if _DEBUG
        logger << "Load failed: " << ex2.GetUTF8NoConvert() << std::endl;
#endif
    }
    EX_END_CATCH(SwallowAllExceptions);
    return klass;
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
    logger << "Invoke:" << method->m_pszDebugClassName << "::" << method->m_pszDebugMethodName << "," << method->m_pszDebugMethodSignature << std::endl;
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
            TypeHandle argTypeHandle;
            auto corType = argIt.GetArgType(&argTypeHandle);
            if (!argTypeHandle.IsNull() && !argTypeHandle.IsFullyLoaded())
            {
                ClassLoader::EnsureLoaded(argTypeHandle);
            }
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
                switch (corType)
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
        {
            auto retSlot = invoker.Call_RetArgSlot(args.data());
            auto returnType = invoker.GetMetaSig()->GetReturnType();
            switch (returnType)
            {
            case ELEMENT_TYPE_ARRAY:
            case ELEMENT_TYPE_PTR:
            case ELEMENT_TYPE_FNPTR:
            case ELEMENT_TYPE_OBJECT:
            case ELEMENT_TYPE_CLASS:
            case ELEMENT_TYPE_SZARRAY:
            case ELEMENT_TYPE_STRING:
                ret = OBJECTREFToObject(ArgSlotToObj(retSlot));
                break;
            default:
                ret = OBJECTREFToObject(MscorlibBinder::GetElementType(returnType)->Box(&retSlot));
                break;
            }
        }
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
    if (klass == klassc) return true;
    if (check_interfaces && klassc->IsInterface())
    {
        if (klass->ImplementsInterface(klassc)) return true;
    }
    else if(!klass->IsInterface() && !klass->IsArray() && klass != klassc)
    {
        if (klass->CanCastToClassNoGC(klassc) == TypeHandle::CanCast) return true;
    }

    if(klassc == g_pObjectClass) return true;
    return false;
}

void mono_class_set_userdata(MonoClass *klass, void* userdata)
{
    klass->m_userData = userdata;
}

MonoDomain * mono_domain_get()
{
    return GetAppDomain();
}

MonoClass* mono_class_get_nesting_type(MonoClass *klass)
{
    CONTRACTL
    {
        NOTHROW;
        GC_TRIGGERS;
        MODE_ANY;
    }
    CONTRACTL_END;

    if (!klass->GetClass()->IsNested()) return nullptr;
    auto typeDef = klass->GetCl();
    mdTypeDef enclosingTypeDef;
    if (FAILED(klass->GetMDImport()->GetNestedClassProps(typeDef, &enclosingTypeDef)))
    {
        _ASSERT(!"Cannot find enclosing typedef.");
        return nullptr;
    }

    MonoClass* enclosingType;
    EX_TRY
    {
        enclosingType = ClassLoader::LoadTypeDefThrowing(klass->GetModule(), enclosingTypeDef,
            ClassLoader::ThrowIfNotFound,
            ClassLoader::PermitUninstDefOrRef).GetMethodTable();
    }
    EX_CATCH
    {
        enclosingType = nullptr;
    }
    EX_END_CATCH(RethrowTerminalExceptions);
    return enclosingType;
}

const char* mono_class_get_namespace (MonoClass *klass)
{
    LPCSTR namespaceName;
    if (FAILED(klass->GetMDImport()->GetNameOfTypeDef(klass->GetCl(), nullptr, &namespaceName)))
    {
        _ASSERT(!"Cannot get namespace.");
        return nullptr;
    }
    return namespaceName;
}

const char* mono_class_get_name(MonoClass *klass)
{
    LPCSTR className;
    if (FAILED(klass->GetMDImport()->GetNameOfTypeDef(klass->GetCl(), &className, nullptr)))
    {
        _ASSERT(!"Cannot get class name.");
        return nullptr;
    }
    return className;
}

gboolean mono_unity_class_is_interface(MonoClass* klass)
{
    return klass->IsInterface();
}

gboolean mono_unity_class_is_abstract(MonoClass* klass)
{
    return klass->IsAbstract();
}

gboolean mono_class_is_generic(MonoClass *klass)
{
    return klass->IsGenericTypeDefinition();
}

gboolean mono_class_is_inflated(MonoClass *klass)
{
    return klass->HasInstantiation();
}

MonoClass* mono_class_get_parent(MonoClass *klass)
{
    return klass->GetParentMethodTable();
}

guint32 mono_signature_get_param_count(MonoMethodSignature *sig)
{
    MetaSig metaSig(sig);
    return metaSig.NumFixedArgs();
}

MonoType* mono_signature_get_return_type(MonoMethodSignature *sig)
{
    MetaSig metaSig(sig);
    TypeHandle typeHandle;
    metaSig.GetReturnTypeNormalized(&typeHandle);
    return typeHandle.AsPtr();
}

MonoType* mono_class_get_type(MonoClass *klass)
{
    return TypeHandle(klass).AsPtr();
}

MonoReflectionType* mono_type_get_object(MonoDomain *domain, MonoType *type)
{
    CONTRACTL
    {
        NOTHROW;
        GC_TRIGGERS;
        MODE_ANY;
    }
    CONTRACTL_END;

    
    MonoReflectionType* reflectionType = nullptr;
    EX_TRY
    {
        GCX_COOP();
        auto ref = TypeHandle::FromPtr(type).GetManagedClassObject();
        if (ref != NULL)
        {
            reflectionType = static_cast<ReflectClassBaseObject*>(
                OBJECTREFToObject(ref));
        }
    }
    EX_CATCH
    {
        reflectionType = nullptr;
    }
    EX_END_CATCH(RethrowTerminalExceptions);
    return reflectionType;
}

MonoClass* mono_class_get_element_class(MonoClass *klass)
{
    if (klass->IsArray())
        return klass->GetApproxArrayElementTypeHandle().AsMethodTable();//array.cpp 478 Line(May be NULL)
    if (klass->IsEnum())
        return MscorlibBinder::GetElementType(klass->GetInternalCorElementType());
    _ASSERT(!"Cannot get element class.");
    return nullptr;
}

MonoType* mono_signature_get_params(MonoMethodSignature *sig, gpointer *iter)
{
    MetaSig metasig(sig);
    ArgIterator argIt(&metasig);

    DWORD arg = 0;
    for (; TransitionBlock::InvalidOffset != argIt.GetNextOffset(); arg++)
        if (arg == reinterpret_cast<DWORD>(*iter)) break;
    if (arg == argIt.NumFixedArgs()) return nullptr;
    *iter = reinterpret_cast<gpointer>(arg + 1);
    TypeHandle argTypeHandle;
    auto corType = argIt.GetArgType(&argTypeHandle);
    if (argTypeHandle.IsNull())
        argTypeHandle = MscorlibBinder::GetElementType(corType);
    return argTypeHandle.AsPtr();
}

MonoClass * mono_class_from_mono_type(MonoType *type)
{
    return TypeHandle::FromPtr(type).GetMethodTable();
}
