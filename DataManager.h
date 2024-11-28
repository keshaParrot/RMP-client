#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include "CPUData.h" 
#include "GPUData.h"
#include "RAMData.h"

extern TFT_eSPI tft;

class DataManager {
  private:
    String lastDataGUID;
    unsigned long lastTimeGetData = 0;
    unsigned long previousMillis = 0;
    const long interval = 1000;
    bool isConnectionLostMessageTrue;

    bool isDataNew(String jsonData);

  public:
    DataManager();
    void checkConnection();
    bool updateData(CPUData* CPUData, GPUData* GPUData, RAMData* RAMData);
};

#endif  // DATA_MANAGER_H
