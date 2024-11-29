#include "ScreenManager.h"


void ScreenManager::updateText(String newText, int x, int y, int fontSize) {
  tft.fillRect(x-5, y-5, tft.textWidth(newText, fontSize) + 15, tft.fontHeight(fontSize)+5, TFT_BLACK);
  tft.drawString(newText, x, y, fontSize);
}

void ScreenManager::showCPUScreen() {
  tft.fillRect(10, 10, 50, 50, TFT_GREEN);
  String dataCpu = String(cpu.centralLoad) + " % " + String(cpu.temperature) + " C";
  tft.drawString(cpu.name, 65, 10, 4);  
  updateText(dataCpu, 65, 40, 4);

  int gridHeight = 3 * squareSize + (3 - 1) * verticalSpacing;
  int startX = 10;
  int startY = tft.height() - gridHeight - 10;
  
  size_t count = cpu.coreUnits.size();
  int unitIndex = 0;
  int drawnSquares = 0;
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (drawnSquares < count) {
        int x = startX + col * (squareSize + horizontalSpacing);
        int y = startY + row * (squareSize + verticalSpacing);
        tft.fillRect(x, y, squareSize, squareSize, TFT_BLACK);
        clgm->drawCoreLoadGraph(x, y, squareSize, squareSize,unitIndex);
        int coreX = x + squareSize + 5;
        int coreY = y;

        if (unitIndex < count) {
          updateText(cpu.coreUnits[unitIndex].name, coreX, coreY, 1);
          coreY += 12;
          for(int l = 0; l < cpu.coreUnits[unitIndex].load.size() ; l++ ){
            String coreLoad = cpu.coreUnits[unitIndex].load.getKey(l) + ": " + cpu.coreUnits[unitIndex].load.getValue(l) + " %";
            updateText(coreLoad, coreX, coreY, 1);
            coreY += 12;
          }
          updateText(String(cpu.coreUnits[unitIndex].temperature) + " C", coreX, coreY, 1);
          coreY += 12;
          updateText(String(cpu.coreUnits[unitIndex].frequency) + " MHz", coreX, coreY, 1);
          coreY += 12;
          updateText(String(cpu.coreUnits[unitIndex].voltage) + " V", coreX, coreY, 1);
          unitIndex++;
        }
        drawnSquares++;
      }
    }
  }
}

void ScreenManager::showGPUScreen() {
  tft.fillRect(10, 10, 50, 50, TFT_GREEN);
  tft.drawString(gpu.name, 65, 30, 4);  

  String fLine = "Central Load: " + String(gpu.load) + "%  "+ "Core frequency: " + String(gpu.frequency[0]) + " MHz  " + "temp: " + String(gpu.temperature)+"C";
  String sLine = "Memory Load: " + String(gpu.memoryLoad) + "%  " + "Memory frequency: " + String(gpu.frequency[1]) + " MHz  " + "volt: " + String(gpu.voltage)+"V";
  
  auto centerX = [](String text) -> int16_t {
    int16_t width = tft.textWidth(text);
    return (tft.width() - width) / 2;
  };
  
  updateText(fLine, centerX(fLine) - 50, 80, 2);
  updateText(sLine, centerX(sLine) - 50, 100, 2);

  int rectWidth = 380;
  int rectHeight = 150;

  int rectX = ((tft.width() - rectWidth) / 2 )- 50;
  int rectY = tft.height() - rectHeight - 15;

  tft.fillRect(rectX, rectY, rectWidth, rectHeight, TFT_BLACK);
  gdgm->drawAllGraphs(rectX, rectY, rectWidth, rectHeight);
  for(int i = 0; i < 6;i++){
    tft.fillRect(390, 170+(i*20), 12, 12, colors[i]);
  }
  tft.drawString("Load", 410, 172, 1);  
  tft.drawString("Core freq", 410, 192, 1);  
  tft.drawString("Memory freq", 410, 212, 1);  
  tft.drawString("Temperature", 410, 232, 1);  
  tft.drawString("Voltage", 410, 252, 1);  
  tft.drawString("Fan speed", 410, 272, 1);  
}

void ScreenManager::showRAMScreen() {
  tft.fillRect(10, 10, 50, 50, TFT_GREEN);
  tft.drawString("Random-Access Memory", 65, 30, 4);  

  String fLine = "Load: " + String(ram.load) + "%  "+ "Total: " + String(ram.total) + "GB";
  String sLine = "Virtual Used: " + String(ram.virtualUsed)+"GB  " + "Used: " + String(ram.used) + "GB";
  String tLine = "Vitrual Available: " + String(ram.virtualAvailable)+"GB  " + "Available: " + String(ram.available) + "GB";
  
  auto centerX = [](String text) -> int16_t {
    int16_t width = tft.textWidth(text);
    return (tft.width() - width) / 2;
  };

  updateText(fLine, centerX(fLine)-20, 80, 2);
  updateText(sLine, centerX(sLine)-20, 100, 2);
  updateText(tLine, centerX(tLine)-20, 120, 2);

  int rectWidth = 100;
  int rectHeight = 100;
  int horizontalSpacing = 30;
  int totalWidth = 3 * rectWidth + 2 * horizontalSpacing;
  
  int startX = (tft.width() - totalWidth) / 2;
  int startY = tft.height() - rectHeight - 15;
  
  tft.drawString(rdgm->getConfigVal(0) + ":", startX, startY - 25, 2);  
  rdgm->drawCoreLoadGraph(startX, startY, rectWidth, rectHeight, 0);
  
  tft.drawString(rdgm->getConfigVal(1) + ":", startX + rectWidth + horizontalSpacing, startY - 25, 2);  
  rdgm->drawCoreLoadGraph(startX + rectWidth + horizontalSpacing, startY, rectWidth, rectHeight, 1);
  
  tft.drawString(rdgm->getConfigVal(2) + ":", startX + 2 * (rectWidth + horizontalSpacing), startY - 25, 2);  
  rdgm->drawCoreLoadGraph(startX + 2 * (rectWidth + horizontalSpacing), startY, rectWidth, rectHeight, 2);
}

void ScreenManager::showHomeScreen() {
  tft.fillRect(10, 10, 50, 50, TFT_GREEN);
  tft.drawString(String(HEADER_TITLE), 70, 30, 4);  

  int linePosx = tft.width() /3;
  tft.drawLine(linePosx, 100, linePosx, 300, TFT_GREEN);
  tft.drawLine(linePosx*2, 100, linePosx*2, 300, TFT_GREEN);

  tft.drawString("CPU:", 10, 85, 4);  
  tft.drawString("Central:", 10, 115, 2); 
  updateText("* load: " + String(cpu.centralLoad) +"%", 10, 135, 1);
  updateText("* Temperature: " + String(cpu.temperature)+"C", 10, 150, 1);
  
  tft.drawString("Per core:", 10, 170, 2); 
  int coreCount = cpu.coreUnits.size();
  float avgLoad = 0.0f;
  float avgTemp = 0.0f;
  float avgVolt = 0.0f;

  for (size_t i = 0; i < cpu.coreUnits.size(); ++i) {
    for (int j = 0; j < cpu.coreUnits[i].load.size(); ++j) {
        avgLoad += cpu.coreUnits[i].load.getValue(j);
    }
    avgTemp += cpu.coreUnits[i].temperature;
    avgVolt += cpu.coreUnits[i].voltage;
  }

  updateText("* Load: " + String(avgLoad / coreCount)+"%", 10, 190, 1);
  updateText("* Temperature: " + String(avgTemp / coreCount)+"C", 10, 205, 1);
  updateText("* Voltage: " + String(avgVolt / coreCount)+"V", 10, 220, 1);

  int secondSectionPosX = linePosx + 10;
  tft.drawString("GPU:", secondSectionPosX, 85, 4);  
  updateText("Load: " + String(gpu.load) +"%", secondSectionPosX, 135, 1);
  updateText("Memory load: " + String(gpu.memoryLoad)+"%", secondSectionPosX, 150, 1);
  updateText("Temperature: " + String(gpu.temperature)+"C", secondSectionPosX, 165, 1);
  updateText("Fan Speed: " + String(gpu.fanSpeed)+"RPM", secondSectionPosX, 180, 1);

  int thirdSectionPosX = linePosx * 2 + 10;
  tft.drawString("RAM:", thirdSectionPosX, 85, 4);  
  updateText("Load: " + String(ram.load) +"%", thirdSectionPosX, 135, 1);
  updateText("Total: " + String(ram.total)+"GB", thirdSectionPosX, 150, 1);
  updateText("Used: " + String(ram.used)+"GB", thirdSectionPosX, 165, 1);
  updateText("Available: " + String(ram.available)+"GB", thirdSectionPosX, 180, 1);
}
