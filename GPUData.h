#ifndef GPUDATA_H
#define GPUDATA_H

class GPUData {
  public:
    char name[20];
    float load;
    long frequency[2];
    float memoryLoad;
    float temperature;
    float voltage;
    float fanSpeed;

    GPUData();
};

#endif  // GPUDATA_H
