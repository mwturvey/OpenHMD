#include "vl_driver.h"
#include <string>
#include <vector>
#include <map>
#include <stdio.h>

class ViveLibre {
 public:
  vl_driver* driver;
  ViveLibre();
  ~ViveLibre();
  void connect();
  std::map<int, std::vector<float>> pollAngles();
  std::string get_config();
};
