#include "storageLogic.h"
#include "Arduino.h"
#include <EEPROMWearLevel.h>

#define EEPROM_LAYOUT_VERSION 1
#define AMOUNT_OF_INDEXES 1

#define INDEX_DATA_CONTAINER 0

typedef struct DataContainer {
  int startTemp;
  int diffTemp;
  int operatingMode;
} DataContainer;

float _srHumidity = 0.0f;
float _srTemperature = 0.0f;

DataContainer _data = {0,0,0};

void storageSetupAndRetrieveData() {
    EEPROMwl.begin(EEPROM_LAYOUT_VERSION, AMOUNT_OF_INDEXES);

    EEPROMwl.get(INDEX_DATA_CONTAINER, _data);
    if(getStorageStartTemperature() == 0 &&
    getStorageDifferenceTemperature() == 0 &&
    getStorageOperatingMode() == 0) {
      Serial.println("No default found for Settings. Setting default");
      _data = {.startTemp = 22, .diffTemp = 3, .operatingMode = 0};
    }

}

void storagePersistData() {

  EEPROMwl.put(INDEX_DATA_CONTAINER, _data);
}


int getStorageStartTemperature() {
  return _data.startTemp;
}

int getStorageDifferenceTemperature() {
  return _data.diffTemp;
}

OperationgMode getStorageOperatingMode() {
  return _data.operatingMode;
}

float getStorageHumidity() {
  return _srHumidity;
}

float getStorageTemperature() {
  return _srTemperature;
}

void setStorageStartTemperature(int temp) {
  _data.startTemp = temp;
}

void setStorageDifferenceTemperature(int diff) {
  _data.diffTemp = diff;
}
void setStorageOperatingMode(OperationgMode mode) {
  // Needs mode check
  _data.operatingMode = mode;
}

void setStorageHumidity(float humidity) {
  _srHumidity = humidity;
}

void setStorageTemperature(float temperature) {
  _srTemperature = temperature;
}
