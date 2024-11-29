#ifndef COREUNITGRAPHMANAGER_H
#define COREUNITGRAPHMANAGER_H

#include <vector>
#include <TFT_eSPI.h> 
#include "RingBuffer.h"
#include "CoreUnit.h"
#include "CPUData.h"
#include "config.h"

extern TFT_eSPI tft;

class CoreUnitGraphManager {
  private:
    std::vector<RingBuffer<float, 7>> coreBuffers;

  public:
    CoreUnitGraphManager(size_t coreCount);
    void updateData(CPUData data);
    void drawCoreLoadGraph(int x, int y, int width, int height, int coreIndex);
};

#endif  // COREUNITGRAPHMANAGER_H
