#ifndef CPUDATA_H
#define CPUDATA_H

#include <vector>
#include "CoreUnit.h"

class CPUData {
  public:
    char name[30];
    float centralLoad;
    double temperature;
    std::vector<CoreUnit> coreUnits;

    CPUData(); 
};

#endif  // CPUDATA_H
