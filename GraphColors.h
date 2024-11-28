#ifndef GRAPHCOLORS_H
#define GRAPHCOLORS_H

#include <cstddef>
#include <cstdint>
#include <TFT_eSPI.h>

struct GraphColors {
    uint16_t loadColor = TFT_GREEN;   
    uint16_t frequencyColor = TFT_BLUE;
    uint16_t memoryLoadColor = TFT_CYAN;
    uint16_t temperatureColor = TFT_RED;
    uint16_t voltageColor = TFT_YELLOW; 
    uint16_t fanSpeedColor = TFT_ORANGE;

    GraphColors();

    uint16_t operator[](size_t index) const;
    size_t size() const;
};

#endif  // GRAPHCOLORS_H
