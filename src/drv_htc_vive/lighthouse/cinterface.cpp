#include "vl_python.h"
#include <iostream>
#include <map>
#include <json/json.h>

ViveLibre *vivelibre_instance = nullptr;

extern "C" hid_device* vivelibre_get_hmd_device() {
	return vivelibre_instance->driver->hmd_device;
}

extern "C" hid_device* vivelibre_get_hmd_imu_device() {
	return vivelibre_instance->driver->hmd_imu_device;
}

extern "C" hid_device* vivelibre_get_watchman_dongle_device() {
	return NULL;
}

extern "C" hid_device* vivelibre_get_hmd_light_sensor_device() {
	return NULL;
}

int* object_points;
int object_points_count = 0;

int angle_range_h[] = {32, 156};
int angle_range_v[] = {25, 149};
float ticks_per_degree = 2222.22;

extern "C" void vive_libre_init() {
	printf("Init Vive Libre\n");
	vivelibre_instance = new ViveLibre();

	return;

	//std::cout << "Polling .." <<std::endl;
	std::map<int, std::vector<float>> angles = vivelibre_instance->pollAngles();
	//std::cout << "Polled!" <<std::endl;


	int image_points[angles.size()][2];
	int imgpointcnt = 0;
	for (std::map<int,std::vector<float>>::iterator it=angles.begin(); it!=angles.end(); ++it) {
		//int image_point[2] = { (it->second[0] / ticks_per_degree) - angle_range_v[0], (it->second[1] / ticks_per_degree) - angle_range_h[0] };
		image_points[imgpointcnt][0] = (it->second[0] / ticks_per_degree) - angle_range_v[0];
		image_points[imgpointcnt][1] = (it->second[1] / ticks_per_degree) - angle_range_h[0];
		imgpointcnt++;
	}

	std::string config = vivelibre_instance->get_config();
	//std::cout << "Vive config: " << config << std::endl;
	std::cout << "Got config!" << std::endl;

	Json::Value root;   // starts as "null"; will contain the root value after parsing
	Json::Reader reader;
	reader.parse(config, root);

	// Get the value of the member of root named 'my-encoding', return 'UTF-32' if there is no
	// such member.
	//std::string my_encoding = root.get("my-encoding", "UTF-32" ).asString();

	// Get the value of the member of root named 'my-plug-ins'; return a 'null' value if
	// there is no such member.
	const Json::Value lh_config = root["lighthouse_config"];
	//std::cout << "lighthouse config: " << lh_config << std::endl;
	const Json::Value lh_modelPoints = lh_config["modelPoints"];
	object_points_count = lh_modelPoints.size();
	//object_points = new
	for ( int index = 0; index < lh_modelPoints.size(); ++index ) { // Iterates over the sequence elements.
		double point[3];
		for (int p = 0; p < 3; p++) {
			Json::Value mp(lh_modelPoints[index]);
			//std::cout << "mp " << index << ": " << mp.get(p, NULL) << std::endl;
			point[p] = mp.get(p, NULL).asDouble();
		}
		std::cout << "Point " << point[0] << " " << point[1] << " " << point[2] << std::endl;
	}


	//yourlib::setIndentLength( root["my-indent"].get("length", 3).asInt() );
	//yourlib::setIndentUseSpace( root["my-indent"].get("use_space", true).asBool() );


}

extern "C" float* vivelibre_poll() {
	float* pos = (float*) malloc(sizeof(float) * 3);
	//TODO: implement this function https://github.com/lubosz/OSVR-Vive-Libre/blob/pnp/python/test.py#L110
	pos[0] = 0;
	pos[1] = 1;
	pos[2] = 2;
	return pos;
}
