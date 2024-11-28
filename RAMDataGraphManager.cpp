#include "RAMDataGraphManager.h"

RAMDataGraphManager::RAMDataGraphManager() {
    ramBuffer.resize(3, RingBuffer<float, 7>());
}

void RAMDataGraphManager::addVal(int index, float value) {
    if (index < ramBuffer.size()) {
        ramBuffer[index].add(value);
    }
}

float RAMDataGraphManager::getRAMElementValue(int element, const RAMData &ramData) {
    if (element == LOAD) {
        return ramData.load;
    } else if (element == USED) {
        return ramData.used;
    } else if (element == VUSED) {
        return ramData.virtualUsed;
    } else if (element == AVAILABLE) {
        return ramData.available;
    } else if (element == VAVAILABLE) {
        return ramData.virtualAvailable;
    }
    return 0.0f;
}

float RAMDataGraphManager::normalizeValue(float value, float maxValue) {
    return (value / maxValue) * 100.0f;
}

String RAMDataGraphManager::convertConfigToString(int element) {
    switch (element) {
        case 0: return "Load";
        case 1: return "Used";
        case 2: return "Virtual Used";
        case 3: return "Available";
        case 4: return "Virtual Available";
        default: return "null";
    }
}

String RAMDataGraphManager::getConfigVal(int index) {
    switch (index) {
        case 0: return convertConfigToString(RAM_FIRST_ELEMENT);
        case 1: return convertConfigToString(RAM_SECOND_ELEMENT);
        case 2: return convertConfigToString(RAM_THIRD_ELEMENT);
        default: return "null";
    }
}

float RAMDataGraphManager::getGraphData(int index, const RAMData &ramData) {
    switch (index) {
        case 0: return getRAMElementValue(RAM_FIRST_ELEMENT, ramData);
        case 1: return getRAMElementValue(RAM_SECOND_ELEMENT, ramData);
        case 2: return getRAMElementValue(RAM_THIRD_ELEMENT, ramData);
        default: return 0.0f;
    }
}

void RAMDataGraphManager::drawCoreLoadGraph(int x, int y, int width, int height, RAMData &ramData, int graphIndex) {
    if (graphIndex >= ramBuffer.size()) return;

    float dataToPlot = 0.0f;

    if (getConfigVal(graphIndex) != "Load") {
        dataToPlot = normalizeValue(getGraphData(graphIndex, ramData), ramData.total);
    } else {
        dataToPlot = getGraphData(graphIndex, ramData);
    }

    addVal(graphIndex, dataToPlot);

    if (ramBuffer[graphIndex].size() < 2) return;

    tft.fillRect(x - 10, y - 10, width + 10, height + 10, TFT_BLACK);

    int prevX = x;
    int prevY = y + height - (ramBuffer[graphIndex].get(0) * height / 100);

    for (size_t i = 1; i < ramBuffer[graphIndex].size(); i++) {
        int currentX = x + (i * width / (ramBuffer[graphIndex].size() - 1));
        int currentY = y + height - (ramBuffer[graphIndex].get(i) * height / 100);

        tft.drawLine(prevX, prevY, currentX, currentY, TFT_GREEN);
        prevX = currentX;
        prevY = currentY;
    }
    tft.drawRect(x, y, width, height, TFT_WHITE);
}
