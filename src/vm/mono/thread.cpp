#include "common.h"
#include "mono.h"

void mono_thread_current_check_pending_interrupt ()
{
    GetThread()->HandleThreadAbort();
}

MonoThread * mono_thread_current(void)
{
    return GetThread();
}

Thread* s_mainThread = nullptr;

void mono_thread_set_main(MonoThread *thread)
{
    s_mainThread = thread;
}
