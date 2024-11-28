#include "GPUData.h"

GPUData::GPUData() {
    name[0] = '\0';
    load = 0.0;
    frequency[0] = 0;
    frequency[1] = 0;
    memoryLoad = 0.0;
    temperature = 0.0;
    voltage = 0.0;
    fanSpeed = 0.0;
}
