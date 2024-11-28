#ifndef COREUNITGRAPHMANAGER_H
#define COREUNITGRAPHMANAGER_H

#include <vector>
#include <TFT_eSPI.h> 
#include "RingBuffer.h"
#include "CoreUnit.h"
#include "config.h"

extern TFT_eSPI tft;

class CoreUnitGraphManager {
  private:
    std::vector<RingBuffer<float, 7>> coreBuffers;

    void updateCore(int coreIndex, float value);

  public:
    CoreUnitGraphManager(size_t coreCount);

    void drawCoreLoadGraph(int x, int y, int width, int height, CoreUnit &coreUnit, int coreIndex);
};

#endif  // COREUNITGRAPHMANAGER_H
