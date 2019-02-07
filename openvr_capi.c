/*
 * Utility functions and workarounds to quirks in the OpenVR C API.
 * 
 * references:
 * - discussion forum at https://steamcommunity.com/app/358720
 * - https://github.com/VsevolodGolovanov/openvr_c_dabbling.git
 */
#include "openvr_capi.h"

#include <stdio.h>

static const char* VR_IVRFnTable_Prefix = "FnTable:";

static TrackedPropertyError ovr_get_device_string(char* buffer, uint32_t len,
                                                  VR_IVRSystem* hmd,
                                                  TrackedDeviceIndex_t device,
                                                  TrackedDeviceProperty property)
{
    TrackedPropertyError error;
    /*const uint32_t required = */hmd->GetStringTrackedDeviceProperty(device, property, buffer, len, &error);
    return error;
}

EVRInitError ovr_setup(struct ovr_t* ovr)
{
    char table_name[128] = {0};

    enum EVRInitError error = EVRInitError_VRInitError_None;
    VR_InitInternal(&error, EVRApplicationType_VRApplication_Scene);

    if (error != EVRInitError_VRInitError_None)
    {
        return error;
    }

    /*
     * interface: VR_IVRSystem
     */

    sprintf(table_name, "%s%s", VR_IVRFnTable_Prefix, IVRSystem_Version);
    ovr->hmd = (VR_IVRSystem*)VR_GetGenericInterface(table_name, &error);

    if (ovr->hmd == NULL || error != EVRInitError_VRInitError_None)
    {
        return error;
    }

    /*
     * interface: VR_IVRRenderModels
     */

    sprintf(table_name, "%s%s", VR_IVRFnTable_Prefix, IVRRenderModels_Version);
    ovr->render_models = (VR_IVRRenderModels*)VR_GetGenericInterface(table_name, &error);

    if (ovr->render_models == NULL || error != EVRInitError_VRInitError_None)
    {
        return error;
    }

    /*
     * property names
     */

    ETrackedPropertyError prop_error = ETrackedPropertyError_TrackedProp_Success;

    prop_error = ovr_get_device_string(
        ovr->system_name,
        sizeof(ovr->system_name),
        ovr->hmd,
        k_unTrackedDeviceIndex_Hmd,
        ETrackedDeviceProperty_Prop_TrackingSystemName_String
    );

    if (prop_error != ETrackedPropertyError_TrackedProp_Success)
    {
        return EVRInitError_VRInitError_Unknown;
    }

    prop_error = ovr_get_device_string(
        ovr->serial_number,
        sizeof(ovr->serial_number),
        ovr->hmd,
        k_unTrackedDeviceIndex_Hmd,
        ETrackedDeviceProperty_Prop_SerialNumber_String
    );

    if (prop_error != ETrackedPropertyError_TrackedProp_Success)
    {
        return EVRInitError_VRInitError_Unknown;
    }

    /*
     * interface: VR_IVRCompositor
     */

    sprintf(table_name, "%s%s", VR_IVRFnTable_Prefix, IVRCompositor_Version);
    ovr->compositor = (VR_IVRCompositor*)VR_GetGenericInterface(table_name, &error);

    if (ovr->compositor == NULL || error != EVRInitError_VRInitError_None)
    {
        return error;
    }

    return EVRInitError_VRInitError_None;
}

void ovr_shutdown(struct ovr_t* ovr)
{
    if (ovr->hmd != NULL)
    {
        VR_ShutdownInternal();
        ovr->hmd = NULL;
    }
}

void ovr_poll_events(struct ovr_t* ovr)
{
    VREvent_t event;

    while (ovr->hmd->PollNextEvent(&event, sizeof(event)))
    {
        /* TODO process event */
    }

    for (TrackedDeviceIndex_t device = 0; device < k_unMaxTrackedDeviceCount; device++)
    {
        VRControllerState_t state;
        if (ovr->hmd->GetControllerState(device, &state, sizeof(state)))
        {
            /* TODO process state */
        }
    }
}
