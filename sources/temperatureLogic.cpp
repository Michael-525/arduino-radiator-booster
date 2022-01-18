#include "temperatureLogic.h"

float _humidity = 0;
float _tempC = 0;
DHT* _sensor;

void setTempSensor(DHT* sensor){
  _sensor = sensor;
}

void updateTempSensor(){
  _humidity = _sensor->readHumidity();
  _tempC = _sensor->readTemperature();
}

float readTempSensorHumidity() {
  return _humidity;
}

float readTempSensorTempC() {
  return _tempC;
}
