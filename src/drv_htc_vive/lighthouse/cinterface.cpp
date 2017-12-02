#include "vl_python.h"
#include <iostream>
#include <map>

extern "C" int* vivelibre_poll() {
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
	std::cout << "Polling .." <<std::endl;
	std::map<int, std::vector<float>> angles = vivelibre_instance->pollAngles();
	std::cout << "Polled!" <<std::endl;
	for (std::map<int,std::vector<float>>::iterator it=angles.begin(); it!=angles.end(); ++it)
		std::cout << it->first << " => " << '\n';
	//TODO: implement this function https://github.com/lubosz/OSVR-Vive-Libre/blob/pnp/python/test.py#L110
	pos[0] = 0;
	pos[1] = 1;
	pos[2] = 2;
	return pos;
}
