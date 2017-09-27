
set(VM_SOURCES_MONO
    mono.cpp
    dl.cpp
    plugin.cpp
    class.cpp
    init.cpp
    thread.cpp
)

convert_to_absolute_path(VM_SOURCES_MONO ${VM_SOURCES_MONO})

add_precompiled_header(common.h ../common.cpp VM_SOURCES_MONO)
add_library_clr(cee_mono ${VM_SOURCES_MONO})
