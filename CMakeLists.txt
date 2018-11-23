#
# project: fips-openvr
#
fips_begin_lib(openvr_api)

include_directories(
    openvr/headers
    openvr/src
    openvr/src/vrcommon
)

fips_dir(openvr/src GROUP "Src")

fips_files(
    openvr_api_public.cpp
    jsoncpp.cpp
)

fips_dir(openvr/src/vrcommon GROUP "VRCommon")

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
