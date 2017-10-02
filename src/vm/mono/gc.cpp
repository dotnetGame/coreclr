#include "common.h"
#include "mono.h"
#undef max

int mono_gc_max_generation (void)
{
    return GCHeapUtilities::GetGCHeap()->GetMaxGeneration();
}

void mono_gc_collect(int generation)
{
    GCX_COOP();
    GCHeapUtilities::GetGCHeap()->GarbageCollect(generation);
}

MonoArray * mono_array_new(MonoDomain *domain, MonoClass *eclass, mono_array_size_t n)
{
    CONTRACTL
    {
        NOTHROW;
        GC_TRIGGERS;
        MODE_ANY;
    }
    CONTRACTL_END;

    MonoArray* array;
    EX_TRY
    {
        GCX_COOP();
        INT32 bounds = n;
        array = OBJECTREFToObject(AllocateArrayEx(TypeHandle(eclass).MakeSZArray(), &bounds, 1));
    }
    EX_CATCH
    EX_END_CATCH(SwallowAllExceptions);
    return array;
}

guint32 mono_gchandle_new(MonoObject *obj, gboolean pinned)
{
    CONTRACTL
    {
        NOTHROW;
        GC_TRIGGERS;
        MODE_ANY;
    }
    CONTRACTL_END;

    OBJECTHANDLE handle;
    EX_TRY
    {
        auto mgr = GCHandleUtilities::GetGCHandleManager();
        auto store = mgr->GetGlobalHandleStore();
        GCX_COOP();
        handle = store->CreateHandleOfType(obj, pinned ? HNDTYPE_PINNED : HNDTYPE_DEFAULT);

    }
    EX_CATCH
    EX_END_CATCH(SwallowAllExceptions);
    _ASSERT(reinterpret_cast<uintptr_t>(handle) <= std::numeric_limits<guint32>().max());
    return reinterpret_cast<guint32>(handle);
}
