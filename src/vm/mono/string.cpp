#include "common.h"
#include "mono.h"

MonoString* mono_string_new_wrapper (const char *text)
{
    if (!text) return nullptr;
    GCX_COOP();
    return STRINGREFToObject(StringObject::NewString((LPCUTF8)text));
}
