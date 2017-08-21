//========= Copyright Valve Corporation ============//
#define VR_API_EXPORT 1
#include "openvr.h"
#include "ivrclientcore.h"
#include "envvartools_public.h"
#include "hmderrors_public.h"
#include <string.h>

using vr::EVRInitError;
using vr::IVRSystem;
using vr::IVRClientCore;
using vr::VRInitError_None;

namespace vr
{

static void *g_pVRModule = NULL;
static IVRClientCore *g_pHmdSystem = NULL;


typedef void* (*VRClientCoreFactoryFn)(const char *pInterfaceName, int *pReturnCode);

static uint32_t g_nVRToken = 0;

uint32_t VR_GetInitToken()
{
        printf("inittoken requested\n");
	return g_nVRToken;
}

EVRInitError VR_LoadHmdSystemInternal();
void CleanupInternalInterfaces();


uint32_t VR_InitInternal( EVRInitError *peError, vr::EVRApplicationType eApplicationType )
{
        printf("pretending to initinternal\n");
        *peError = VRInitError_None;
	return ++g_nVRToken;
}

void VR_ShutdownInternal()
{
        printf("pretending to shutdowninternal\n");
	++g_nVRToken;
}

EVRInitError VR_LoadHmdSystemInternal()
{
        printf("pretending to load hmdsysteminternal...\n");
	return VRInitError_None;
}


class OpenHMDRenderModels : vr::IVRRenderModels {
    EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, RenderModel_t **ppRenderModel ) {
        printf("rendermodel async load requested: %s\n", pchRenderModelName);
        //TODO: load
        return VRRenderModelError_None;
    }

    void FreeRenderModel( RenderModel_t *pRenderModel ){
        printf("free render model\n");
        //TODO:
    }

    /** Loads and returns a texture for use in the application. */
    EVRRenderModelError LoadTexture_Async( TextureID_t textureId, RenderModel_TextureMap_t **ppTexture ) {
        printf("load texture async requested: %d\n", textureId);
        //TODO:
        return VRRenderModelError_None;
    }

    void FreeTexture( RenderModel_TextureMap_t *pTexture ) {
        printf("free texture requested\n");
        //TODO:

    }

    EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D ) {
        printf("\n");
        //TODO:
        return VRRenderModelError_None;
    }

    EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture ) {
        printf("\n");
        //TODO:
        return VRRenderModelError_None;
    }

    void FreeTextureD3D11( void *pD3D11Texture2D ) {
        printf("\n");
        //TODO:
    }

    uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen ) {
        printf("get render model name for %d\n", unRenderModelIndex);
        //TODO:
        char* name = (char*) "OpenHMDModel";
        *pchRenderModelName = *name;
        return 0;
    }

    uint32_t GetRenderModelCount() {
        printf("get render model count\n");
        //TODO:
        return 1;
    }

    uint32_t GetComponentCount( const char *pchRenderModelName ) {
        printf("get component count, 0 not supported\n");
        //TODO:
        return 0;
    }

    uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen ) {
        printf("get component name for %s\n", pchRenderModelName);
        //TODO: shouldn't happen with componentcount 0
        return 0;
    }

    uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName ) {
        printf("component button mask\n");
        //TODO:

        return 0;
    }

    uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen ) {
        printf("component render model name\n");
        //TODO:

        return 0;
    }

    bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const vr::VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState ) {
        printf("get component state\n");
        //TODO:
        return false;
    }

    bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName ) {
        printf("render model has component %s: %s\n", pchRenderModelName, pchComponentName);
        //TODO:
        return false;
    }

    uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError ) {
        printf("thumbnail for %s\n", pchRenderModelName);
        //TODO:
        return 0;
    }

    uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError ) {
        printf("render model original path for %s\n", pchRenderModelName);
        //TODO:
        return 0;
    }

    const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error ) {
        printf("string for %d\n", error);
        //TODO:
        return "error" ;
    }
};

class OpenHMDIVRSystem : IVRSystem
{
public:
    void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) {
        printf("recommended render target size\n");
        //TODO:
        *pnWidth = 800;
        *pnHeight = 600;
    }

    HmdMatrix44_t GetProjectionMatrix( EVREye eEye, float fNearZ, float fFarZ ) {
        printf("projection matrix for eye\n");
        if (eEye == EVREye::Eye_Left) {
            printf("left");
        } else {
            printf("right");
        }
        //TODO:

        HmdMatrix44_t matrix;
        return matrix;
    }

    void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) {
        printf("projection raw\n");
        //TODO:
    }

    bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates ) {
        //printf("\n");
        //TODO:
        return true;
    }

    HmdMatrix34_t GetEyeToHeadTransform( EVREye eEye ) {
        printf("eye to head transform for eye\n");
        if (eEye == EVREye::Eye_Left) {
            printf("left");
        } else {
            printf("right");
        }
        //TODO:
        HmdMatrix34_t matrix;
        return matrix;
    }

    bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter ) {
        //printf("\n");
        //TODO:

        pfSecondsSinceLastVsync = 0;
        pulFrameCounter = 0;
        return false;
    }
    int32_t GetD3D9AdapterIndex() {
        return 0;
    }

    void GetDXGIOutputInfo( int32_t *pnAdapterIndex ) {
    }

    void GetOutputDevice( uint64_t *pnDevice, ETextureType textureType ) {
        printf("output device\n");
        //TODO:
        *pnDevice = 0;
    }

    bool IsDisplayOnDesktop() {
        printf("extended mode: \n");
        //TODO:
        return true;
    }

    bool SetDisplayVisibility( bool bIsVisibleOnDesktop ) {
        return true;
    }

    void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount ) {
        printf("device to abs tracking pose\n");
        //TODO:
    }

    void ResetSeatedZeroPose() {
        printf("reset seated zero pose\n");
        //TODO:

    }

    HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() {
        printf("get seated zero to standing absolute\n");
        //TODO:

        HmdMatrix34_t matrix;
        return matrix;
    }

    HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() {
        printf("get rar zero to standing absolute\n");
        //TODO:

        HmdMatrix34_t matrix;
        return matrix;
    }

    uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex = k_unTrackedDeviceIndex_Hmd ) {
        printf("get sorted tracked device indices\n");
        //TODO:
        return 0;
    }

    EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId ) {
        printf("tracked device activity for %d\n", unDeviceId);
        //TODO:
        return EDeviceActivityLevel::k_EDeviceActivityLevel_Unknown;
    }


    void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform ) {
        printf("apply transform\n");
        //TODO:
    }

    vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType ) {
        printf("device for role %d\n", unDeviceType);
        if (unDeviceType == ETrackedControllerRole::TrackedControllerRole_Invalid) {
            printf("invalid\n");
        } else if (unDeviceType == ETrackedControllerRole::TrackedControllerRole_LeftHand) {
            printf("left hand\n");
        } else {
            printf("right hand\n");
        }
        //TODO:
        return 0;
    }

    vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex ) {
        printf("controller role for %d\n", unDeviceIndex);
        //TODO:
        return ETrackedControllerRole::TrackedControllerRole_Invalid;
    }

    ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex ) {
        printf("get device class for %d\n", unDeviceIndex);
        //TODO:
        return ETrackedDeviceClass::TrackedDeviceClass_Invalid;
    }

    bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex ) {
        printf("is device connected %d\n", unDeviceIndex);
        //TODO:
        return false;
    }

    bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) {
        //printf("bool tracked property\n");
        //TODO:
        return false;
    }

    float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) {
        //printf("\n");
        //TODO:
        return false;
    }

    int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) {
        return 0;
    }

    uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) {
        return 0;
    }

    HmdMatrix34_t GetMatrix34TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) {
        HmdMatrix34_t matrix;
        return matrix;
    }

    uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError = 0L ) {
        return 0;
    }

    const char *GetPropErrorNameFromEnum( ETrackedPropertyError error ) {
        printf("error %d\n", error);
        //TODO:
        return "error";
    }

    bool PollNextEvent( VREvent_t *pEvent, uint32_t uncbVREvent ) {
        //printf("\n");
        //TODO:
        return false;
    }

    bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose ) {
        //printf("\n");
        //TODO:
        return false;
    }

    const char *GetEventTypeNameFromEnum( EVREventType eType ) {
        printf("event type from enum %d\n", eType);
        //TODO:
        return "event";
    }

    HiddenAreaMesh_t GetHiddenAreaMesh( EVREye eEye, EHiddenAreaMeshType type = k_eHiddenAreaMesh_Standard ) {
        printf("hidden area mesh\n");
        //TODO:

    }

    bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize ) {
        //printf("\n");
        //TODO:

        return false;
    }

    bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose ) {
        //printf("\n");
        //TODO:
        return false;
    }

    void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec ) {
        printf("trigger haptic pulse of duration %f ms\n", usDurationMicroSec / 1000.);
        //TODO:

    }

    const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId ) {
        printf("button id name from enum %d\n", eButtonId);
        //TODO:
        return "buttonid";
    }

    const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType ) {
        printf("controller axis name from enum %d\n", eAxisType);
        //TODO:
        return "axis";
    }

    bool CaptureInputFocus() {
        printf("capture input focus \n");
        //TODO:
        return true;
    }

    void ReleaseInputFocus() {
        printf("release input focus\n");
        //TODO:
    }

    bool IsInputFocusCapturedByAnotherProcess() {
        printf("is input focus captured by other process?\n");
        //TODO:
        return false;
    }

    uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize ) {
        printf("debug request\n");
        //TODO:
        return 0;
    }

    vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex ) {
        printf("firmware update\n");
        //TODO:
        return EVRFirmwareError::VRFirmwareError_None;
    }

    void AcknowledgeQuit_Exiting() {
        printf("acknowledge quit\n");
        //TODO:
    }

    void AcknowledgeQuit_UserPrompt() {
        printf("acknowledge quit prompt\n");
        //TODO:
    }
};

void *VR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
{
        printf("getgenericinterface version %s \n", pchInterfaceVersion);

        if (strcmp (pchInterfaceVersion, "IVRSystem_016") == 0) {
            printf("generic interface: IVRSystem_016\n");
            OpenHMDIVRSystem *m_pRenderModels = new OpenHMDIVRSystem();
            return m_pRenderModels;
        }

        if (strcmp (pchInterfaceVersion, "IVRRenderModels_005") == 0) {
            printf("generic interface: IVRRenderModels_005: Rendermodels\n");
            OpenHMDRenderModels *m_pRenderModels = new OpenHMDRenderModels();
            return m_pRenderModels;

        }

        *peError = VRInitError_None;
	return nullptr;
}

bool VR_IsInterfaceVersionValid(const char *pchInterfaceVersion)
{
        printf("interfaceversion %s is valid requested, confirming..\n", pchInterfaceVersion);
	return true;
}

bool VR_IsHmdPresent()
{
        printf("IsHmdPresent requested, confirming..\n");
        return true;
}

/** Returns true if the OpenVR runtime is installed. */
bool VR_IsRuntimeInstalled()
{
        printf("Runtime installed requested, confirming..\n");
        return true;
}


/** Returns where OpenVR runtime is installed. */
const char *VR_RuntimePath()
{
        printf("Runtime path requested, pretending \"\"\n");
        return "";
}


/** Returns the symbol version of an HMD error. */
const char *VR_GetVRInitErrorAsSymbol( EVRInitError error )
{
	if( g_pHmdSystem )
		return g_pHmdSystem->GetIDForVRInitError( error );
	else
		return GetIDForVRInitError( error );
}


/** Returns the english string version of an HMD error. */
const char *VR_GetVRInitErrorAsEnglishDescription( EVRInitError error )
{
	if ( g_pHmdSystem )
		return g_pHmdSystem->GetEnglishStringForHmdError( error );
	else
		return GetEnglishStringForHmdError( error );
}


VR_INTERFACE const char *VR_CALLTYPE VR_GetStringForHmdError( vr::EVRInitError error );

/** Returns the english string version of an HMD error. */
const char *VR_GetStringForHmdError( EVRInitError error )
{
	return VR_GetVRInitErrorAsEnglishDescription( error );
}

}
