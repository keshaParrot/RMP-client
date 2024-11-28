#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <TFT_eSPI.h>
#include "CoreUnitGraphManager.h"
#include "GPUDataGraphManager.h" 
#include "RAMDataGraphManager.h" 
#include "CPUData.h" 
#include "GPUData.h"
#include "RAMData.h"
#include "GraphColors.h"

extern TFT_eSPI tft;
extern GraphColors colors;
extern CoreUnitGraphManager* clgm;
extern GPUDataGraphManager* gdgm;
extern RAMDataGraphManager* rdgm;


class ScreenManager{
  private:
    RAMData& ram;
    CPUData& cpu;
    GPUData& gpu;

    const int squareSize = 60;
    const int verticalSpacing = 15;
    const int horizontalSpacing = 90;

  public:
    ScreenManager(RAMData& ram, CPUData& cpu, GPUData& gpu)
        : ram(ram), cpu(cpu), gpu(gpu) {}

    void showCPUScreen();
    void showGPUScreen();
    void showRAMScreen();
    void showHomeScreen();
    void updateText(String newText, int x, int y, int fontSize);
};


#endif  // SCREEN_MANAGER_H