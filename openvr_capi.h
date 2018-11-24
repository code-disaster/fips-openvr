#pragma once
#include "openvr/headers/openvr_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * function prototypes disabled in openvr_capi.h
 */
intptr_t VR_InitInternal(EVRInitError* peError, EVRApplicationType eType);
void VR_ShutdownInternal();
bool VR_IsHmdPresent();
intptr_t VR_GetGenericInterface(const char* pchInterfaceVersion, EVRInitError* peError);
bool VR_IsRuntimeInstalled();
const char* VR_GetVRInitErrorAsSymbol(EVRInitError error);
const char* VR_GetVRInitErrorAsEnglishDescription(EVRInitError error);

extern bool VR_IsInterfaceVersionValid(const char* pchInterfaceVersion);

/*
 * function table typedefs
 */
typedef struct VR_IVRSystem_FnTable VR_IVRSystem;
typedef struct VR_IVRExtendedDisplay_FnTable VR_IVRExtendedDisplay;
typedef struct VR_IVRTrackedCamera_FnTable VR_IVRTrackedCamera;
typedef struct VR_IVRApplications_FnTable VR_IVRApplications;
typedef struct VR_IVRChaperone_FnTable VR_IVRChaperone;
typedef struct VR_IVRChaperoneSetup_FnTable VR_IVRChaperoneSetup;
typedef struct VR_IVRCompositor_FnTable VR_IVRCompositor;
typedef struct VR_IVROverlay_FnTable VR_IVROverlay;
typedef struct VR_IVRRenderModels_FnTable VR_IVRRenderModels;
typedef struct VR_IVRNotifications_FnTable VR_IVRNotifications;
typedef struct VR_IVRSettings_FnTable VR_IVRSettings;
typedef struct VR_IVRScreenshots_FnTable VR_IVRScreenshots;
typedef struct VR_IVRResources_FnTable VR_IVRResources;
typedef struct VREvent_t VREvent_t;

struct ovr_t
{
    VR_IVRSystem* hmd;
    VR_IVRRenderModels* render_models;
    VR_IVRCompositor* compositor;
    char system_name[64];
    char serial_number[64];
};

EVRInitError ovr_setup(struct ovr_t* ovr);

void ovr_shutdown(struct ovr_t* ovr);

void ovr_poll_events(struct ovr_t* ovr);

#ifdef __cplusplus
}
#endif
