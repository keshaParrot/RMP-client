#ifndef GPUDATAGRAPHMANAGER_H
#define GPUDATAGRAPHMANAGER_H

#include <TFT_eSPI.h>
#include "RingBuffer.h"
#include "GPUData.h"
#include "GraphColors.h"

extern TFT_eSPI tft;
extern GraphColors colors;

class GPUDataGraphManager {
  private:
    struct GPUDataBuffers {
      RingBuffer<float, 10> loadBuffer;
      RingBuffer<float, 10> frequencyBuffer;
      RingBuffer<float, 10> memoryLoadBuffer;
      RingBuffer<float, 10> temperatureBuffer;
      RingBuffer<float, 10> voltageBuffer;
      RingBuffer<float, 10> fanSpeedBuffer;
    };

    float minVoltage = 0.5f;
    float maxVoltage = 1.5f;
    float minFrequency = 0.0f;
    float maxFrequency = 3000.0f;

    GPUDataBuffers gpuBuffers;

    void updateGPUData(const GPUData &gpuData);
    void updateVoltageRange(float voltage);
    void updateFrequencyRange(float frequency);
    void drawSingleGraph(int x, int y, int width, int height, const RingBuffer<float, 10> &buffer, uint16_t color);

  public:
    void drawAllGraphs(GPUData &gpuData, int x, int y, int width, int height);
};

#endif  // GPUDATAGRAPHMANAGER_H
