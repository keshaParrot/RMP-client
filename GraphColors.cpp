#include "GraphColors.h"

GraphColors::GraphColors() {
    loadColor = TFT_GREEN;   
    frequencyColor = TFT_BLUE;
    memoryLoadColor = TFT_CYAN;
    temperatureColor = TFT_RED;
    voltageColor = TFT_YELLOW; 
    fanSpeedColor = TFT_ORANGE;
}

uint16_t GraphColors::operator[](size_t index) const {
    static const uint16_t allColors[] = {
        loadColor, frequencyColor, memoryLoadColor,
        temperatureColor, voltageColor, fanSpeedColor
    };
    if (index < sizeof(allColors) / sizeof(allColors[0])) {
        return allColors[index];
    }
    return TFT_WHITE;
}

size_t GraphColors::size() const {
    return 6;
}
