#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include "config.h"

TFT_eSPI tft = TFT_eSPI();

#include "CPUData.h" 
#include "GPUData.h"
#include "RAMData.h"
#include "CoreUnitGraphManager.h"
#include "RAMDataGraphManager.h"
#include "GPUDataGraphManager.h"
#include "DataManager.h"
#include "ScreenManager.h"
#include "GraphColors.h"

//TODO 
// перенесення коду в окремі .h  і cpp файли
// поправлення графіків (криві показання в ядрах де немає потоків)
// окремі методи малювання і додавання данних до менеджерів граф
// зміна квадратиків на пнг

const int buttonCPUPin = 2; 
const int buttonGPUPin = 3;
const int buttonRAMPin = 4;
const int buttonHomePin = 5;

int screenIndex = 0;
int oldScreenIndex = -1;

DataManager* dataManager;
CoreUnitGraphManager* clgm;
GPUDataGraphManager* gdgm;
RAMDataGraphManager* rdgm;
ScreenManager* screenManager;
CPUData cpu;
GPUData gpu;
RAMData ram;


void setup() {
  Serial.begin(9600);
  
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK); 
  tft.setTextColor(TFT_GREEN); 
  tft.setTextSize(1); 
  
  showInitScreen("Initializating serial, please wait...");
  unsigned long startMillis = millis();
  while (millis() - startMillis < 5000);

  pinMode(buttonCPUPin, INPUT_PULLUP);
  pinMode(buttonGPUPin, INPUT_PULLUP);
  pinMode(buttonRAMPin, INPUT_PULLUP);
  pinMode(buttonHomePin, INPUT_PULLUP);

  dataManager = new DataManager();
  
  tft.fillScreen(TFT_BLACK);
  showInitScreen("waiting for data...");

  while(!dataManager->updateData(&cpu, &gpu, &ram));
  
  Serial.println("cpu.coreUnits.size() "+ String(cpu.coreUnits.size()));
    clgm = new CoreUnitGraphManager(cpu.coreUnits.size());
    gdgm = new GPUDataGraphManager();
    rdgm = new RAMDataGraphManager();

    screenManager = new ScreenManager(ram,cpu,gpu);
    
}
void showScreen(){
  if(screenIndex != oldScreenIndex){
    oldScreenIndex = screenIndex; 
    tft.fillScreen(TFT_BLACK);
  }
  if(screenIndex == 0){
    screenManager->showHomeScreen();
  }else if(screenIndex == 1){
    screenManager->showCPUScreen();
  }else if(screenIndex == 2){
    screenManager->showGPUScreen();
  }else if(screenIndex == 3){
    screenManager->showRAMScreen();
  }
}
void loop() {
  if(digitalRead(buttonHomePin) == LOW){
    screenIndex = 0;
  }else if(digitalRead(buttonCPUPin) == LOW){
    screenIndex = 1;
  }else if(digitalRead(buttonGPUPin) == LOW){
    screenIndex = 2;
  }else if(digitalRead(buttonRAMPin) == LOW){
    screenIndex = 3;
  }
  dataManager->checkConnection();
  if(dataManager->updateData(&cpu, &gpu, &ram)){
    showScreen();
  }
}
void showInitScreen(String message) {
  tft.drawString("Resource Monitor is running,", 10, 10, 4);  
  tft.drawString(message, 10, 50, 4);  
}

