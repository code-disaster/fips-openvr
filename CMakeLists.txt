#
# project: fips-openvr
#
fips_begin_lib(openvr_api)

add_definitions(
    -DVR_API_PUBLIC
)

if (FIPS_WIN64)
    add_definitions(
        -DWIN64
    )
endif()

fips_files(
    openvr.h
    openvr_capi.h
    openvr_capi.c
)

include_directories(
    openvr/headers
    openvr/src
    openvr/src/vrcommon
)

fips_dir(openvr/headers GROUP "headers")

fips_files(
    openvr.h
    openvr_capi.h
)

fips_dir(openvr/src GROUP "src")

fips_files(
    openvr_api_public.cpp
    jsoncpp.cpp
)

fips_dir(openvr/src/vrcommon GROUP "vrcommon")

fips_files(
    dirtools_public.cpp
    envvartools_public.cpp
    pathtools_public.cpp
    sharedlibtools_public.cpp
    hmderrors_public.cpp
    vrpathregistry_public.cpp
    strtools_public.cpp
)

fips_end_lib()
