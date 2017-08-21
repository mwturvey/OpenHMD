//========= Copyright Valve Corporation ============//
#define VR_API_EXPORT 1
#include "openvr.h"
#include "ivrclientcore.h"
#include "envvartools_public.h"
#include "hmderrors_public.h"

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


void *VR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
{
        printf("getgenericinterface version %s \n", pchInterfaceVersion);
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

