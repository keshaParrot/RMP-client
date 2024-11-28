#include "GPUDataGraphManager.h"

void GPUDataGraphManager::updateGPUData(const GPUData &gpuData) {
    updateVoltageRange(gpuData.voltage);
    gpuBuffers.loadBuffer.add(gpuData.load);

    updateFrequencyRange(gpuData.frequency[0]);
    float frequencyNormalized = (gpuData.frequency[0] - minFrequency) / (maxFrequency - minFrequency) * 100.0f;
    gpuBuffers.frequencyBuffer.add(frequencyNormalized);

    float memoryLoadClamped = std::min(gpuData.memoryLoad, 100.0f);
    gpuBuffers.memoryLoadBuffer.add(memoryLoadClamped);

    gpuBuffers.temperatureBuffer.add(gpuData.temperature / 100.0f * 100.0f);

    float voltageNormalized = (gpuData.voltage - minVoltage) / (maxVoltage - minVoltage) * 100.0f;
    gpuBuffers.voltageBuffer.add(voltageNormalized);

    gpuBuffers.fanSpeedBuffer.add(gpuData.fanSpeed / 5000.0f * 100.0f);
}

void GPUDataGraphManager::updateVoltageRange(float voltage) {
    minVoltage = std::min(minVoltage, voltage);
    maxVoltage = std::max(maxVoltage, voltage);
}

void GPUDataGraphManager::updateFrequencyRange(float frequency) {
    minFrequency = std::min(minFrequency, frequency);
    maxFrequency = std::max(maxFrequency, frequency);
}

void GPUDataGraphManager::drawSingleGraph(int x, int y, int width, int height, const RingBuffer<float, 10> &buffer, uint16_t color) {
    if (buffer.size() < 2) return;

    int prevX = x;
    int prevY = y + height - (buffer.get(0) * height / 100);

    for (size_t i = 1; i < buffer.size(); i++) {
        int currentX = x + (i * width / (buffer.size() - 1));
        int currentY = y + height - (buffer.get(i) * height / 100);

        tft.drawLine(prevX, prevY, currentX, currentY, color);
        prevX = currentX;
        prevY = currentY;
    }
    tft.drawRect(x, y, width, height, TFT_WHITE);
}

void GPUDataGraphManager::drawAllGraphs(GPUData &gpuData, int x, int y, int width, int height) {
    updateGPUData(gpuData);

    int fieldHeight = height / 6;

    drawSingleGraph(x, y, width, fieldHeight, gpuBuffers.loadBuffer, colors[0]);
    drawSingleGraph(x, y + fieldHeight, width, fieldHeight, gpuBuffers.frequencyBuffer, colors[1]);
    drawSingleGraph(x, y + 2 * fieldHeight, width, fieldHeight, gpuBuffers.memoryLoadBuffer, colors[2]);
    drawSingleGraph(x, y + 3 * fieldHeight, width, fieldHeight, gpuBuffers.temperatureBuffer, colors[3]);
    drawSingleGraph(x, y + 4 * fieldHeight, width, fieldHeight, gpuBuffers.voltageBuffer, colors[4]);

    if (gpuData.fanSpeed != -1) {
        drawSingleGraph(x, y + 5 * fieldHeight, width, fieldHeight, gpuBuffers.fanSpeedBuffer, colors[5]);
    }
}
