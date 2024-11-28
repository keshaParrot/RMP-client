#include "DataManager.h"

DataManager::DataManager() {
  lastTimeGetData = millis();
}

bool DataManager::isDataNew(String jsonData) {
  int idIndex = jsonData.indexOf("\"Id\":");
  if (idIndex != -1) {
    int idStart = jsonData.indexOf("\"", idIndex + 5) + 1;
    int idEnd = jsonData.indexOf("\"", idStart);
    String currentGUID = jsonData.substring(idStart, idEnd);

    if (currentGUID != lastDataGUID) {
      lastDataGUID = currentGUID;  
      return true; 
    }
  }
  return false;
}

void DataManager::checkConnection() {
  unsigned long currentTime = millis();
  String connectionMessage = "Server connection lost";
  if (currentTime - lastTimeGetData >= 10000) {
    tft.drawString(connectionMessage, 300, 10, 2);
    isConnectionLostMessageTrue == true;  
  } else if(isConnectionLostMessageTrue){
    tft.fillRect(300, 10, tft.textWidth(connectionMessage, 2), tft.fontHeight(2), TFT_BLACK); 
  }
}

bool DataManager::updateData(CPUData* CPUData, GPUData* GPUData, RAMData* RAMData) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    String jsonInputStr = Serial.readStringUntil('\n');
    const char* jsonInput = jsonInputStr.c_str();

    if (isDataNew(jsonInput)) {
      lastTimeGetData = millis();
      JsonDocument doc;

      DeserializationError error = deserializeJson(doc, jsonInput, strlen(jsonInput));

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return false;
      }

      JsonObject Cpu = doc["Cpu"];
      JsonArray Cpu_coreUnits = Cpu["coreUnits"];

      Cpu["name"].as<String>().toCharArray(CPUData->name, sizeof(CPUData->name));
      CPUData->centralLoad = Cpu["centralLoad"];
      CPUData->temperature = Cpu["temperature"];
      CPUData->coreUnits.clear();

      for (int i = 0; i < Cpu_coreUnits.size(); i++) {
        JsonObject Cpu_coreUnit = Cpu_coreUnits[i];
        CoreUnit CU;
        Cpu_coreUnit["name"].as<String>().toCharArray(CU.name, sizeof(CU.name));
        CU.temperature = Cpu_coreUnit["temperature"];
        CU.frequency = Cpu_coreUnit["frequency"];
        CU.voltage = Cpu_coreUnit["voltage"];

        JsonObject load = Cpu_coreUnits[i]["load"];
        for (JsonPair kv : load) {
          CU.load.add(kv.key().c_str(), kv.value());
        }

        CPUData->coreUnits.push_back(CU);
      }

      JsonObject Gpu = doc["Gpu"];
      Gpu["name"].as<String>().toCharArray(GPUData->name, sizeof(GPUData->name));
      GPUData->load = Gpu["load"];
      GPUData->memoryLoad = Gpu["memoryLoad"];
      GPUData->temperature = Gpu["temperature"];
      GPUData->voltage = Gpu["voltage"];
      GPUData->fanSpeed = Gpu["fanSpeed"];

      for (int i = 0; i < sizeof(Gpu["frequency"]) / sizeof(Gpu["frequency"][0]); i++) {
        GPUData->frequency[i] = Gpu["frequency"][i];
      }

      JsonObject Memory = doc["Memory"];
      RAMData->load = Memory["load"];
      RAMData->total = Memory["total"];
      RAMData->used = Memory["used"];
      RAMData->virtualUsed = Memory["virtualUsed"];
      RAMData->available = Memory["available"];
      RAMData->virtualAvailable = Memory["virtualAvailable"];

      return true;
    }    
    return false;
  }
  return false;
}
