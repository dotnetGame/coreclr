#include "common.h"
#include "mono.h"
#include <algorithm>

int mono_class_get_userdata_offset ()
{
    return offsetof(EEClass, m_userData);
}
