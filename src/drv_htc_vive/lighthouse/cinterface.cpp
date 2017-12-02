#include "vl_python.h"
#include <iostream>
#include <map>

extern "C" int* vivelibre_poll() {
	static int angle_range_h[] = {32, 156};
	static int angle_range_v[] = {25, 149};
	static float ticks_per_degree = 2222.22;
	int* pos = (int*) malloc(sizeof(int) * 3);
	static ViveLibre *vivelibre_instance = nullptr;
	if (!vivelibre_instance) {
		printf("Init Vive Libre\n");
		vivelibre_instance = new ViveLibre();
		//vivelibre_instance->connect();
		std::string config = vivelibre_instance->get_config();
		//std::cout << "Vive config: " << config << std::endl;
		std::cout << "Got config!" << std::endl;
	}

	//std::cout << "Polling .." <<std::endl;
	std::map<int, std::vector<float>> angles = vivelibre_instance->pollAngles();
	//std::cout << "Polled!" <<std::endl;

	int object_points[angles.size()];
	int image_points[angles.size()][2];
	int imgpointcnt = 0;
	for (std::map<int,std::vector<float>>::iterator it=angles.begin(); it!=angles.end(); ++it) {
		//int image_point[2] = { (it->second[0] / ticks_per_degree) - angle_range_v[0], (it->second[1] / ticks_per_degree) - angle_range_h[0] };
		image_points[imgpointcnt][0] = (it->second[0] / ticks_per_degree) - angle_range_v[0];
		image_points[imgpointcnt][1] = (it->second[1] / ticks_per_degree) - angle_range_h[0];
		imgpointcnt++;
	}



	//TODO: implement this function https://github.com/lubosz/OSVR-Vive-Libre/blob/pnp/python/test.py#L110
	pos[0] = 0;
	pos[1] = 1;
	pos[2] = 2;
	return pos;
}
