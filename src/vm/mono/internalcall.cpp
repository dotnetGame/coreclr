#include "common.h"
#include "mono.h"

void mono_add_internal_call (const char *name, gconstpointer method)
{
    logger << "Adding internal call: " << name << std::endl;
}
