#include <LiquidCrystal.h>
#include "storageLogic.h"
#include "displayLogic.h"
#include "temperatureLogic.h"
#include "userInputLogic.h"
#include "menuLogic.h"

// General
#define INITIAL_WAIT_TIME 500
#define UPDATE_RATE 80

// TempSensor
#define Type DHT11
int pinTempSensor = 2;

// LCD
int pinLcdRs = 7;
int pinLcdEn = 8;
int pinLcdD4 = 9;
int pinLcdD5 = 10;
int pinLcdD6 = 11;
int pinLcdD7 = 12;

// Fan Relay
int pinRelay = 4;

void setup() {
  Serial.begin(9600);

  // LCD Setup
  LiquidCrystal lcd(pinLcdRs, pinLcdEn, pinLcdD4, pinLcdD5, pinLcdD6, pinLcdD7);
  lcd.begin(16, 2);
  setDisplay(&lcd);

  // Temp Sensor Setup
  DHT sensor(pinTempSensor, Type);
  sensor.begin();
  setTempSensor(&sensor);
  delay(INITIAL_WAIT_TIME);

  // Relay Setup
  pinMode(pinRelay, OUTPUT);

  // Storage
  storageSetupAndRetrieveData();
}


void transferSensorData() {
  setStorageTemperature(readTempSensorTempC());
  setStorageHumidity(readTempSensorHumidity());
}

void updateFans() {

  // if Mode is Auto or on:
  if(getStorageOperatingMode() == on){
    digitalWrite(pinRelay, HIGH);
    return;
  } 
  
  if (getStorageOperatingMode() == off) {
    digitalWrite(pinRelay, LOW);
    return;
  }
  // Automatic mode
  // If readout temp is higher than setup temp
  if ((int)getStorageTemperature() > getStorageStartTemperature()) {
    // turn on.
    digitalWrite(pinRelay, HIGH); 
  } else if ((int)getStorageTemperature() < (getStorageStartTemperature() - getStorageDifferenceTemperature())){
    digitalWrite(pinRelay, LOW);
  }
} 

void loop() {
  // Update Loop
 
  updateTempSensor();
  transferSensorData();
  readUserInput();

  if(wasUpArrowPressed()) { menuOnUpPressed(); Serial.println("UpArrowPressed"); }
  if(wasDownArrowPressed()) { menuOnDownPressed(); Serial.println("DownArrowPressed"); }
  if(wasIncreaseArrowPressed()) { menuOnIncreasePressed(); Serial.println("IncreaseArrowPressed"); }
  if(wasDecreaseArrowPressed()) { menuOnDecreasePressed(); Serial.println("DecreaseArrowPressed"); }

  display(menuEntryName(), menuEntryDescName());

  
  updateFans();
  delay(UPDATE_RATE);
}

inline void digitalToggle(byte pin) {
  digitalWrite(pin, !digitalRead(pin));
}
