SteamVR Plugin for OpenHMD Devices

Build:
Just run `cmake` and `make` in the OpenHMD directory. The OPENHMD_STEAMVR option is enabled by default.

Run:
First register the driver with SteamVR:

    ~/.local/share/Steam/SteamApps/common/SteamVR/bin/linux64/vrpathreg adddriver ~/OpenHMD/build/

Then copy the steamvr.vrsettings file that disables the lighthouse and oculus default driver:

    cp ~/OpenHMD/steamvr/steamvr.vrsettings ~/.local/share/Steam/config/steamvr.vrsettings

Don't forget to make a backup if you have special SteamVR settings. Now run SteamVR and check ~/.local/share/Steam/logs/vrserver.txt for errors.
