# What is this

The aim is to implement libopenvr_api.dll/libopenvr_api.so on top of OpenHMD.

Games and applications using OpenVR/SteamVR will ship this library (or rely on the library to be present in /usr/lib/).

Valve's libopenvr_api is just a wrapper around their proprietary and x86-only SteamVR runtime. However, libopenvr_api is documented and "open source", so other backends than SteamVR can be implemented, in this case OpenHMD.

Once this library is finished, the libopenvr_api shipped in any SteamVR application or game can be swapped out and the application can be used with only the OpenHMD drivers, Steam and SteamVR are not needed.

# Status

hellovr_opengl runs and renders something to its preview window.

The HMD is hardcoded as deviceindex 0, controller support has to wait until the HMD tracking works.

In WaitGetPoses the rotation of the HMD is set. TODO: do it right.

The compositor is unimplemented. TODO: 1. make a fullscreen window with SDL that shows the incoming textures. 2. apply openhmd's universal distortion shader.

If you want to hack on it: Just build this OpenHMD branch with cmake and by default it will build OpenHMD/src/libopenvr/libopenvr_api.so.

For easy testing OpenHMD/src/libopenvr/hellovr_opengl is built and linked to the libopenvr_api.so library in the same directory - no need to install anything. Start ./hellovr_opengl, watch the output and implement the relevant functions in the skeleton classes in openvr_api_public.cpp.

There's a lot of trash source code copied from the openvr repository in this branch. It's just there to get off the ground. Eventually most of it will be deleted.
