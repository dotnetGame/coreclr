#include "common.h"
#include "mono.h"

void mono_security_set_core_clr_platform_callback (MonoCoreClrPlatformCB callback)
{
    
}

void mono_security_set_mode(MonoSecurityMode mode)
{

}

void mono_verifier_set_mode(MiniVerifierMode mode)
{

}

bool s_socketSecurityEnabled = false;

void mono_unity_socket_security_enabled_set(gboolean enabled)
{
    s_socketSecurityEnabled = enabled;
}
