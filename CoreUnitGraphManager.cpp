#include "CoreUnitGraphManager.h"

CoreUnitGraphManager::CoreUnitGraphManager(size_t coreCount) {
    coreBuffers.resize(coreCount);
}

void CoreUnitGraphManager::updateData(CPUData data) {
  float dataToPlot;
  for (size_t i = 0; i < data.coreUnits.size(); i++) {
    dataToPlot = 0.0f;

    CoreUnit& coreUnit = data.coreUnits[i];

    #if CPU_ELEMENT == FLOAD
      dataToPlot = coreUnit.load.getValue(0);
    #elif CPU_ELEMENT == SLOAD
        dataToPlot = coreUnit.load.size() == 2 ? coreUnit.load.getValue(1) : coreUnit.load.getValue(0);
    #elif CPU_ELEMENT == AVGLOAD
        if (coreUnit.load.size() == 2) {
            dataToPlot = (coreUnit.load.getValue(0) + coreUnit.load.getValue(1)) / 2;
        } else {
            dataToPlot = coreUnit.load.getValue(0);
        }
    #elif CPU_ELEMENT == TEMP
        dataToPlot = coreUnit.temperature;
    #elif CPU_ELEMENT == FREQ
        dataToPlot = coreUnit.frequency;
    #elif CPU_ELEMENT == VOLT
        dataToPlot = coreUnit.voltage;
    #endif
    
    coreBuffers[i].add(dataToPlot);
  }
}

void CoreUnitGraphManager::drawCoreLoadGraph(int x, int y, int width, int height, int coreIndex) {
    if (coreIndex >= coreBuffers.size()) return;

    if (coreBuffers[coreIndex].size() < 2) return;

    tft.drawRect(x, y, width, height, TFT_WHITE);

    int prevX = x;
    int prevY = y + height - (coreBuffers[coreIndex].get(0) * height / 100);

    for (size_t i = 1; i < coreBuffers[coreIndex].size(); i++) {
        int currentX = x + (i * width / (coreBuffers[coreIndex].size() - 1));
        int currentY = y + height - (coreBuffers[coreIndex].get(i) * height / 100);

        tft.drawLine(prevX, prevY, currentX, currentY, TFT_GREEN);
        prevX = currentX;
        prevY = currentY;
    }
}
