#ifndef STORAGE_LOGIC_H
#define STORAGE_LOGIC_H

enum OperationgMode {
  automatic = 0,
  on = 1,
  off = 2
};

// Needs to be called beforehand, will load from persistance
void storageSetupAndRetrieveData();
void storagePersistData();

int getStorageStartTemperature();
int getStorageDifferenceTemperature();
OperationgMode getStorageOperatingMode();
float getStorageHumidity();
float getStorageTemperature();

void setStorageStartTemperature(int temp);
void setStorageDifferenceTemperature(int diff);
void setStorageOperatingMode(OperationgMode mode);
void setStorageHumidity(float humidity);
void setStorageTemperature(float temperature);

#endif
