/*
 * OpenHMD - Free and Open Source API and drivers for immersive technology.
 * Copyright (C) 2013 Fredrik Hultin.
 * Copyright (C) 2013 Jakob Bornecrantz.
 * Distributed under the Boost 1.0 licence, see LICENSE for full text.
 */

/* OSVR SDK Driver */

#include <string.h>
#include "../openhmdi.h"

#include <osvr/ClientKit/ContextC.h>
#include <osvr/ClientKit/InterfaceC.h>
#include <osvr/ClientKit/InterfaceStateC.h>
#include <osvr/ClientKit/ParametersC.h>

typedef struct {
   ohmd_device base;
   OSVR_ClientContext osvrctx;
   OSVR_ClientInterface head;
   OSVR_PoseState state;
} osvr_sdk_priv;

static void update_device(ohmd_device* device)
{
   osvr_sdk_priv* priv = (osvr_sdk_priv*)device;
   if(!priv)
      return;
   osvrClientUpdate(priv->osvrctx);
   OSVR_TimeValue timestamp;
   OSVR_ReturnCode ret =
   osvrGetPoseState(priv->head, &timestamp, &(priv->state));
   //if (ret != OSVR_RETURN_SUCCESS) {
      //printf("No pose state!\n");
   //}
}

static int getf(ohmd_device* device, ohmd_float_value type, float* out)
{
   osvr_sdk_priv* priv = (osvr_sdk_priv*)device;
   
   switch(type){
      case OHMD_ROTATION_QUAT: 
         out[0] = osvrQuatGetX(&(priv->state.rotation));
         out[1] = osvrQuatGetY(&(priv->state.rotation));
         out[2] = osvrQuatGetZ(&(priv->state.rotation));
         out[3] = osvrQuatGetW(&(priv->state.rotation));
         break;
         
      case OHMD_POSITION_VECTOR:
         out[0] = osvrVec3GetX(&(priv->state.translation));
         out[1] = osvrVec3GetY(&(priv->state.translation));
         out[2] = osvrVec3GetZ(&(priv->state.translation));
         break;
         
      case OHMD_DISTORTION_K:
         // TODO this should be set to the equivalent of no distortion
         memset(out, 0, sizeof(float) * 6);
         break;
         
      default:
         ohmd_set_error(priv->base.ctx, "invalid type given to getf (%ud)", type);
         return -1;
         break;
   }
   
   return 0;
}

static void close_device(ohmd_device* device)
{
   LOGD("closing dummy device");
   free(device);
}

static ohmd_device* open_device(ohmd_driver* driver, ohmd_device_desc* desc)
{
   osvr_sdk_priv* priv = ohmd_alloc(driver->ctx, sizeof(osvr_sdk_priv));
   if(!priv)
      return NULL;
   
   priv->osvrctx = osvrClientInit("com.osvr.OpenHMD", 0);
   osvrClientGetInterface(priv->osvrctx, "/me/head", &(priv->head));
   
    const char *path = "/display";

    size_t length;
    osvrClientGetStringParameterLength(priv->osvrctx, path, &length);

    char *displayDescription = malloc(length);
    osvrClientGetStringParameter(priv->osvrctx, path, displayDescription, length);

    printf("Got value of %s:\n%s\n", path, displayDescription);
   
   // Set default device properties
   ohmd_set_default_device_properties(&priv->base.properties);
   
   // Set device properties (imitates the rift values)
   priv->base.properties.hsize = 0.149760f;
   priv->base.properties.vsize = 0.093600f;
   priv->base.properties.hres = 2160;
   priv->base.properties.vres = 1200;
   priv->base.properties.lens_sep = 0.063500f;
   priv->base.properties.lens_vpos = 0.046800f;
   priv->base.properties.fov = DEG_TO_RAD(92.0f);
   priv->base.properties.ratio = (2160.0f / 1200.0f) / 2.0f;
   priv->base.properties.digital_button_count = 4;
   
   // calculate projection eye projection matrices from the device properties
   ohmd_calc_default_proj_matrices(&priv->base.properties);
   
   // set up device callbacks
   priv->base.update = update_device;
   priv->base.close = close_device;
   priv->base.getf = getf;
   
   return (ohmd_device*)priv;
}

static void get_device_list(ohmd_driver* driver, ohmd_device_list* list)
{
   ohmd_device_desc* desc = &list->devices[list->num_devices++];
   
   strcpy(desc->driver, "OpenHMD OSVR SDK Driver");
   strcpy(desc->vendor, "OpenHMD");
   strcpy(desc->product, "OSVR Device");
   
   strcpy(desc->path, "(none)");
   
   desc->driver_ptr = driver;
}

static void destroy_driver(ohmd_driver* drv)
{
   //osvrClientShutdown(priv->osvrctx);
   LOGD("shutting down osvr driver");
   free(drv);
}

ohmd_driver* ohmd_create_osvr_sdk_drv(ohmd_context* ctx)
{
   ohmd_driver* drv = ohmd_alloc(ctx, sizeof(ohmd_driver));
   if(!drv)
      return NULL;
   
   drv->get_device_list = get_device_list;
   drv->open_device = open_device;
   drv->get_device_list = get_device_list;
   drv->open_device = open_device;
   drv->destroy = destroy_driver;
   
   return drv;
}
