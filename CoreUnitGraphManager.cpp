#include "CoreUnitGraphManager.h"

CoreUnitGraphManager::CoreUnitGraphManager(size_t coreCount) {
    coreBuffers.resize(coreCount);
}

void CoreUnitGraphManager::updateCore(int coreIndex, float value) {
    if (coreIndex < coreBuffers.size()) {
        coreBuffers[coreIndex].add(value);
    }
}

void CoreUnitGraphManager::drawCoreLoadGraph(int x, int y, int width, int height, CoreUnit &coreUnit, int coreIndex) {
    if (coreIndex >= coreBuffers.size()) return;

    float dataToPlot = 0.0f;

    #if CPU_ELEMENT == FLOAD
        dataToPlot = coreUnit.load.getValue(1); 
    #elif CPU_ELEMENT == SLOAD
        dataToPlot = coreUnit.load.size() == 2 ? coreUnit.load.getValue(2) : coreUnit.load.getValue(1);
    #elif CPU_ELEMENT == AVGLOAD
        if (coreUnit.load.size() == 2) {
            dataToPlot = (coreUnit.load.getValue(1) + coreUnit.load.getValue(2)) / 2;
        } else {
            dataToPlot = coreUnit.load.getValue(1);
        }
    #elif CPU_ELEMENT == TEMP
        dataToPlot = coreUnit.temperature;
    #elif CPU_ELEMENT == FREQ
        dataToPlot = coreUnit.frequency;
    #elif CPU_ELEMENT == VOLT
        dataToPlot = coreUnit.voltage;
    #endif

    updateCore(coreIndex, dataToPlot);

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
