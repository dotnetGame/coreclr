#include "common.h"
#include "mono.h"

int mono_gc_max_generation (void)
{
    return GCHeapUtilities::GetGCHeap()->GetMaxGeneration();
}

void mono_gc_collect(int generation)
{
    GCX_COOP();
    GCHeapUtilities::GetGCHeap()->GarbageCollect(generation);
}
