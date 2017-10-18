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

MonoThread * mono_thread_attach(MonoDomain *domain)
{
    return SetupThreadNoThrow();
}

void mono_thread_detach(MonoThread *thread)
{
    GetThread()->DetachThread(TRUE);
}

void mono_thread_exiting()
{
    assert(!"mono_thread_exit");
}
