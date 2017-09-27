#include "common.h"
#include "mono.h"

struct MonoDlFallbackHandler
{
    MonoDlFallbackLoad load;
    MonoDlFallbackSymbol symbol;
    MonoDlFallbackClose close;
    void* userData;
};

MonoDlFallbackHandler s_dlFallbackHandler;

MonoDlFallbackHandler * mono_dl_fallback_register (MonoDlFallbackLoad load_func, MonoDlFallbackSymbol symbol_func, MonoDlFallbackClose close_func, void *user_data)
{
    s_dlFallbackHandler = { load_func, symbol_func, close_func, user_data };
    return &s_dlFallbackHandler;
}

MonoException* mono_unity_loader_get_last_error_and_error_prepare_exception ()
{
    assert(!"mono_unity_loader_get_last_error_and_error_prepare_exception");
    throw;
}

void mono_dl_fallback_unregister (MonoDlFallbackHandler *handler)
{
    assert(!"mono_dl_fallback_unregister");
}
