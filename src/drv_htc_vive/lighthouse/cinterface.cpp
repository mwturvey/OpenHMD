#include "vl_python.h"

ViveLibre *vivelibre_instance = nullptr;

extern "C" int vivelibre_poll() {
	if (!vivelibre_instance) {
		printf("Init Vive Libre\n");
		vivelibre_instance = new ViveLibre();
	}
	//TODO: implement this function https://github.com/lubosz/OSVR-Vive-Libre/blob/pnp/python/test.py#L110
	return 0;
}
