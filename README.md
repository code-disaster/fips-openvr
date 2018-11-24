# fips-openvr

fipsified OpenVR SDK

> Builds the _OpenVR API client binding library_ as a static library. Only tested on Windows x64.

> There's an error in the current version of the C bindings. I abstained from forking and patching the submodule. To successfully compile this library, navigate to `openvr/headers/openvr_capi.h` and change the reference to a pointer [in this line](https://github.com/ValveSoftware/openvr/blob/master/headers/openvr_capi.h#L2300).

OpenVR: https://github.com/ValveSoftware/openvr

fips: https://github.com/floooh/fips
