#include "common.h"
#include "mono.h"

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
    assert(!"mono_custom_attrs_has_attr");
    throw;
}
MonoCustomAttrInfo* mono_custom_attrs_from_field (MonoClass *klass, MonoClassField *field)
{
    assert(!"mono_custom_attrs_from_field");
    throw;
}
MonoCustomAttrInfo* mono_custom_attrs_from_method (MonoMethod *method)
{
    assert(!"mono_custom_attrs_from_method");
    throw;
}
MonoCustomAttrInfo* mono_custom_attrs_from_class (MonoClass *klass)
{
    assert(!"mono_custom_attrs_from_class");
    throw;
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
    assert(!"mono_custom_attrs_free");
}