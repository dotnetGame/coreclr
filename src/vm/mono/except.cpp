#include "common.h"
#include "mono.h"

MonoException * mono_exception_from_name_msg (MonoImage *image, const char *name_space, const char *name, const char *msg)
{
    assert(!"mono_exception_from_name_msg");
    throw;
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
void mono_raise_exception (MonoException *ex) 
{
    assert(!"mono_raise_exception");
}
MonoClass* mono_get_exception_class (void)
{
    assert(!"mono_get_exception_class");
    throw;
}