#include "menuLogic.h"
#include "Arduino.h"
#include "storageLogic.h"

#define MENU_SWITCH_NUM_OF_SHOWN_ENTRIES 2
#define MENU_SWITCH_SEC_TO_DISPLAY 3

enum MENU {
  menuInfo,     // only showing readings
  menuPersist,   // showing active mode
  menuTemp,     // showing start temperature
  menuDiff,     // showing turn of temperature as differential
  menuFanMode,  // on, off, auto
  menuSizeOf
};

enum MENU _currMenuPosition = menuInfo;
bool _saved = false;

const char* entryNameFor(enum MENU entry) {

  switch (entry) {
    case menuInfo:
      return "INFO";
    case menuPersist:
      return "SAVE SETTINGS";
    case menuTemp:
      return "TRIGGER ON TEMP";
    case menuDiff:
      return "SHUT OFF DIFF.";
    case menuFanMode:
      return "FAN MODE";
    default:
      return "";
  };
}

const char* _modeCharArr(enum OperationgMode currMode) {
  switch (currMode) {
    case automatic:
      return "Automatic";
    case on:
      return "On";
    case off:
      return "Off";
    default:
      return "Unknown";
  }
}

const char* menuDescNameFor(enum MENU entry) {
  static char desc[17] = { '\0' };

  switch (entry) {
    case menuInfo:
      if (((int)(millis() / (MENU_SWITCH_SEC_TO_DISPLAY * 1000))) % MENU_SWITCH_NUM_OF_SHOWN_ENTRIES == 0) {
        snprintf(desc, sizeof(desc), "Humidity: %d.%01d%%", (int)getStorageHumidity(), (int)(getStorageHumidity() * 10) % 10);
      } else {
        snprintf(desc, sizeof(desc), "Temp: %d.%01d deg C", (int)getStorageTemperature(), (int)(getStorageTemperature() * 10) % 10);
      }
      return desc;
    case menuPersist:
        if(_saved){
          return "SAVED";
        }
      snprintf(desc, sizeof(desc), "< >");
      return desc;
    case menuTemp:
      snprintf(desc, sizeof(desc), "%d deg C", getStorageStartTemperature());
      return desc;
    case menuDiff:
      snprintf(desc, sizeof(desc), "%d deg C", getStorageDifferenceTemperature());
      return desc;
    case menuFanMode:
      return _modeCharArr(getStorageOperatingMode());
    default:
      return "";
  };
}

const char* menuEntryName() {
  return entryNameFor(_currMenuPosition);
}

const char* menuEntryDescName() {
  return menuDescNameFor(_currMenuPosition);
}


void menuOnUpPressed() {
  switch (_currMenuPosition) {
    case menuInfo:
      _currMenuPosition = menuFanMode;
      break;
    case menuPersist:
      _currMenuPosition = menuInfo;
      break;
    case menuTemp:
      _currMenuPosition = menuPersist;
      break;
    case menuDiff:
      _currMenuPosition = menuTemp;
      break;
    case menuFanMode:
      _currMenuPosition = menuDiff;
      break;

    default:
      Serial.println("Unknown up menu entry selected!");
  };
}

void menuOnDownPressed() {
    switch (_currMenuPosition) {
    case menuInfo:
      _currMenuPosition = menuPersist;
      break;
    case menuPersist:
      _currMenuPosition = menuTemp;
      break;
    case menuTemp:
      _currMenuPosition = menuDiff;
      break;
    case menuDiff:
      _currMenuPosition = menuFanMode;
      break;
    case menuFanMode:
      _currMenuPosition = menuInfo;
      break;

    default:
      Serial.println("Unknown down menu entry selected!");
  };
}

void menuOnIncreasePressed() {
    switch (_currMenuPosition) {
    case menuInfo:
      break;
    case menuPersist:
      storagePersistData();
      _saved = true;
      break;
    case menuTemp:
      setStorageStartTemperature(constrain(getStorageStartTemperature() + 1,17,35));
      _saved = false;
      break;
    case menuDiff:
      setStorageDifferenceTemperature(constrain(getStorageDifferenceTemperature() + 1,1,10));
      _saved = false;
      break;
    case menuFanMode:
        if(getStorageOperatingMode() == on) {
          setStorageOperatingMode(off);
        } else if(getStorageOperatingMode() == off) {
          setStorageOperatingMode(automatic);
        } else {
          setStorageOperatingMode(on);
        }
        _saved = false;
      break;
    default:
      break;
  };
}

void menuOnDecreasePressed() {
    switch (_currMenuPosition) {
    case menuInfo:
      break;
    case menuPersist:
      break;
    case menuTemp:
      setStorageStartTemperature(constrain(getStorageStartTemperature() - 1,17,35));
      _saved = false;
      break;
    case menuDiff:
      setStorageDifferenceTemperature(constrain(getStorageDifferenceTemperature() - 1,1,10));
      _saved = false;
      break;
    case menuFanMode:
        if(getStorageOperatingMode() == on) {
          setStorageOperatingMode(automatic);
        } else if(getStorageOperatingMode() == off) {
          setStorageOperatingMode(on);
        } else {
          setStorageOperatingMode(off);
        }
      _saved = false;
      break;
    default:
      break;
  };
}
