==What is this==

The aim is to implement libopenvr_api.dll/libopenvr_api.so on top of OpenHMD.

Games and applications using OpenVR/SteamVR will ship this library (or rely on the library to be present in /usr/lib/).

Valve's libopenvr_api is just a wrapper around their proprietary and x86-only SteamVR runtime. However, libopenvr_api is documented and "open source", so other backends than SteamVR can be implemented, in this case OpenHMD.

Once this library is finished, the libopenvr_api shipped in any SteamVR application or game can be swapped out and the application can be used with only the OpenHMD drivers, Steam and SteamVR are not needed.

==Status==

Basically just stubs that allows a SteamVR application to run, but doesn't actually do anything.

If you want to hack on it: Just build this OpenHMD branch with cmake and by default it will build OpenHMD/src/libopenvr/libopenvr_api.so.

For easy testing OpenHMD/src/libopenvr/hellovr_opengl id built and linked to the libopenvr_api.so library in the same directory - no need to install anything. Start ./hellovr_opengl, watch the output and implement the relevant functions in the skeleton classes in openvr_api_public.cpp.

There are three big classes: IVRSystem, IVRRenderModels and IVRCompositor. Currently none of them do much and are stubbed just enough to report values that hellovr_opengl needs to not crash.
