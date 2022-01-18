#ifndef TEMPERATURE_LOGIC_H
#define TEMPERATURE_LOGIC_H
#include <DHT.h>

void setTempSensor(DHT* sensor);
void updateTempSensor();
float readTempSensorHumidity();
float readTempSensorTempC();

#endif
