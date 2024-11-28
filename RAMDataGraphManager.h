#ifndef RAM_DATA_GRAPH_MANAGER_H
#define RAM_DATA_GRAPH_MANAGER_H

#include <vector>
#include <TFT_eSPI.h>
#include "RingBuffer.h"
#include "RAMData.h" 
#include "config.h" 

extern TFT_eSPI tft;

class RAMDataGraphManager {
  private:
    std::vector<RingBuffer<float, 7>> ramBuffer;

    void addVal(int index, float value);
    float getRAMElementValue(int element, const RAMData &ramData);
    float normalizeValue(float value, float maxValue);
    String convertConfigToString(int element);

  public:
    RAMDataGraphManager();
    String getConfigVal(int index);
    float getGraphData(int index, const RAMData &ramData);
    void drawCoreLoadGraph(int x, int y, int width, int height, RAMData &ramData, int graphIndex);
};

#endif  // RAM_DATA_GRAPH_MANAGER_H
