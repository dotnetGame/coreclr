#include "common.h"
#include "mono.h"
#include <assert.h>

/*glibc 
这个类很可能同样定义在了Unity的源码中
ABI兼容*/
typedef struct _GPtrArray {
    gpointer *pdata;
    guint len;
} custom_growable_array;

typedef void(*WorldStateChanged)();
struct _LivenessState
{
    gint                first_index_in_all_objects;
    custom_growable_array* all_objects;

    MonoClass*          filter;

    custom_growable_array* process_array;
    guint               initial_alloc_count;

    void*               callback_userdata;

    register_object_callback filter_callback;
    WorldStateChanged        onWorldStartCallback;
    WorldStateChanged        onWorldStopCallback;
    guint               traverse_depth; // track recursion. Prevent stack overflow by limiting recurion
};

void mono_unity_liveness_stop_gc_world(LivenessState* state)
{
    assert(!"mono_unity_liveness_stop_gc_world");
}
void mono_unity_liveness_finalize(LivenessState* state)
{
    assert(!"mono_unity_liveness_finalize");
}
void mono_unity_liveness_start_gc_world(LivenessState* state)
{
    assert(!"mono_unity_liveness_start_gc_world");
}
void mono_unity_liveness_free_struct(LivenessState* state)
{
    assert(!"mono_unity_liveness_free_struct");
}
LivenessState* mono_unity_liveness_calculation_begin(MonoClass* filter, guint max_count, register_object_callback callback, void* callback_userdata, WorldStateChanged onWorldStartCallback, WorldStateChanged onWorldStopCallback)
{
    assert(!"mono_unity_liveness_calculation_begin");
    throw;
}
void mono_unity_liveness_calculation_end(LivenessState* state)
{
    assert(!"mono_unity_liveness_calculation_end");
}
gpointer mono_unity_liveness_calculation_from_root_managed(gpointer root_handle, gpointer filter_handle, WorldStateChanged onWorldStartCallback, WorldStateChanged onWorldStopCallback)
{
    assert(!"mono_unity_liveness_calculation_from_root");
    throw;
}
gpointer mono_unity_liveness_calculation_from_statics_managed(gpointer filter_handle, WorldStateChanged onWorldStartCallback, WorldStateChanged onWorldStopCallback)
{
    assert(!"mono_unity_liveness_calculation_from_statics");
    throw;
}

void mono_unity_liveness_calculation_from_root(MonoObject* root, LivenessState* state)
{
    assert(!"mono_unity_liveness_calculation_from_root");
}

void mono_unity_liveness_calculation_from_statics(LivenessState* state)
{
    assert(!"mono_unity_liveness_calculation_from_statics");
}
