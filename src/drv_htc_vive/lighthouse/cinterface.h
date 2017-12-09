#ifndef VIVE_LIBRE_CINTERFACE
#define VIVE_LIBRE_CINTERFACE

void vive_libre_init();
float* vivelibre_poll();
hid_device* vivelibre_get_hmd_device();
hid_device* vivelibre_get_hmd_imu_device();
hid_device* vivelibre_get_watchman_dongle_device();
hid_device* vivelibre_get_hmd_light_sensor_device();

#endif
