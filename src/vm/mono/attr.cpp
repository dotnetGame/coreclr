#include "common.h"
#include "mono.h"
#include <memory>
#include <vector>

struct MonoCustomAttrInfo
{
    Module* module;
    IMDInternalImport* scope;
    std::vector<mdToken> attributeTokens;
};

MonoObject* mono_custom_attrs_get_attr (MonoCustomAttrInfo *ainfo, MonoClass *attr_klass)
{
    assert(!"mono_custom_attrs_get_attr");
    throw;
}
static MonoArray* mono_custom_attrs_construct_by_type (MonoCustomAttrInfo *cinfo, MonoClass *attr_klass)
{
    assert(!"mono_custom_attrs_construct");
}

gboolean mono_custom_attrs_has_attr (MonoCustomAttrInfo *ainfo, MonoClass *attr_klass)
{
    for (auto&& token : ainfo->attributeTokens)
    {
        mdToken tkCtor;
        if (FAILED(ainfo->scope->GetCustomAttributeProps(token, &tkCtor)))
        {
            _ASSERT(!"Cannot get custom attribute props.");
            return false;
        }
        mdToken tkType = TypeFromToken(tkCtor);
        if (tkType != mdtMemberRef && tkType != mdtMethodDef)
            continue; // we only deal with the ctor case
        if (FAILED(ainfo->scope->GetParentToken(tkCtor, &tkType)))
        {
            _ASSERT(!"Cannot get custom attribute type.");
            return false;
        }
        _ASSERTE(TypeFromToken(tkType) == mdtTypeRef || TypeFromToken(tkType) == mdtTypeDef);

        if (ClassLoader::LoadTypeDefOrRefThrowing(ainfo->module, tkType).CanCastTo(TypeHandle(attr_klass)))
            return true;
    }

    return false;
}

MonoCustomAttrInfo* mono_custom_attrs_from_field (MonoClass *klass, MonoClassField *field)
{
    assert(!"mono_custom_attrs_from_field");
    throw;
}

MonoCustomAttrInfo* mono_custom_attrs_from_method (MonoMethod *method)
{
    auto scope = method->GetMDImport();
    HENUMInternalHolder hEnum(scope);
    hEnum.EnumInit(mdtCustomAttribute, method->GetMemberDef());

    auto count = hEnum.EnumGetCount();
    auto info = std::make_unique<MonoCustomAttrInfo>();
    info->module = method->GetModule();
    info->scope = scope;
    info->attributeTokens.resize(count);
    for (size_t i = 0; i < count && scope->EnumNext(&hEnum, &info->attributeTokens[i]); i++);
    return info.release();
}

MonoCustomAttrInfo* mono_custom_attrs_from_class (MonoClass *klass)
{
    auto scope = klass->GetMDImport();
    HENUMInternalHolder hEnum(scope);
    hEnum.EnumInit(mdtCustomAttribute, klass->GetCl());

    auto count = hEnum.EnumGetCount();
    auto info = std::make_unique<MonoCustomAttrInfo>();
    info->module = klass->GetModule();
    info->scope = scope;
    info->attributeTokens.resize(count);
    for (size_t i = 0; i < count && scope->EnumNext(&hEnum, &info->attributeTokens[i]); i++);
    return info.release();
}
MonoCustomAttrInfo* mono_custom_attrs_from_assembly (MonoAssembly *assembly)
{
    assert(!"mono_custom_attrs_from_assembly");
    throw;
}
MonoArray* mono_reflection_get_custom_attrs_by_type (MonoObject *obj, MonoClass *attr_klass)
{
    assert(!"mono_reflection_get_custom_attrs_by_type");
    throw;
}
void mono_custom_attrs_free (MonoCustomAttrInfo *ainfo)
{
    std::unique_ptr<MonoCustomAttrInfo> p(ainfo);
}
