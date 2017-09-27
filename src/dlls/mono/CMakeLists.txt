project(mono)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)
add_definitions(-D_FEATURE_NO_HOST)
add_definitions(-D__MONO__)

add_definitions(-DFEATURE_CORECLR)

include_directories(.)

if(CLR_CMAKE_PLATFORM_UNIX)
  add_compile_options(-fPIE)
endif(CLR_CMAKE_PLATFORM_UNIX)

set(MONO_SOURCES
  mono.cpp
)
if(WIN32)
  # set(ILASM_RESOURCES Native.rc)
  list(APPEND MONO_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/mono.def)
  add_definitions(-DFX_VER_INTERNALNAME_STR=mono.dll)
endif(WIN32)


if(CLR_CMAKE_PLATFORM_UNIX)
  # Need generate a right form of asmparse.cpp to avoid the following options.
  # Clang also produces a bad-codegen on this prebuilt file with optimization.
  # https://github.com/dotnet/coreclr/issues/2305
  add_compile_options(-Wno-delete-non-virtual-dtor)
  add_compile_options(-Wno-deprecated-register)
  add_compile_options(-Wno-array-bounds)
  add_compile_options(-Wno-unused-label)
endif(CLR_CMAKE_PLATFORM_UNIX)

add_library_clr(mono
    SHARED
    ${MONO_SOURCES}
)

set(MONO_LINK_LIBRARIES
  utilcodestaticnohost
  mscorpe
  mdhotdata_full
  corguids
)

if(CLR_CMAKE_PLATFORM_UNIX)
  target_link_libraries(mono
    ${MONO_LINK_LIBRARIES}
    ceefgen
    unixcoreclrloader
    utilcodestaticnohost
    mscorrc_debug
    coreclrpal
    palrt
  )

  # FreeBSD and NetBSD implement dlopen(3) in libc
  if(NOT CMAKE_SYSTEM_NAME STREQUAL FreeBSD AND NOT CMAKE_SYSTEM_NAME STREQUAL NetBSD)
    target_link_libraries(mono
      dl
    )
  endif(NOT CMAKE_SYSTEM_NAME STREQUAL FreeBSD AND NOT CMAKE_SYSTEM_NAME STREQUAL NetBSD)
else()
  target_link_libraries(mono
    ${MONO_LINK_LIBRARIES}
    coreclr
    ole32
    oleaut32
    shell32
  )
endif(CLR_CMAKE_PLATFORM_UNIX)

install_clr(mono)

