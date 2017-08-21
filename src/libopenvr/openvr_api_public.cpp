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

    virtual uint32_t GetComponentCount( const char *pchRenderModelName ) {
        printf("get component count, 0 not supported\n");
        //TODO:
        return 0;
    }

    virtual uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen ) {
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


void *VR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
{
        printf("getgenericinterface version %s \n", pchInterfaceVersion);

        if (strcmp (pchInterfaceVersion, "IVRRenderModels_005") == 0) {
            printf("IVRRenderModels_005: Rendermodels\n");
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
