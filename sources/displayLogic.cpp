#include "displayLogic.h"
#include <Arduino.h>

LiquidCrystal* _lcd;
char _firstRow[17];
char _secondRow[17];

void setDisplay(LiquidCrystal* liquidCrystal) {
  _lcd = liquidCrystal;
}
void display(const char* firstRow, const char* secondRow) {

  if(strcmp(_firstRow, firstRow) == 0 && strcmp(_secondRow, secondRow) == 0) {
    // text identical, nothing to update. Skip.
    // Serial.println("Skipping display update. Text identical");
    return;
  }

  // update str to compare
  strcpy(_firstRow, firstRow);
  strcpy(_secondRow, secondRow);

  // update whole display
  _lcd->clear();
  _lcd->setCursor(0, 0);
  _lcd->print(_firstRow);
  _lcd->setCursor(0, 1);
  _lcd->print(_secondRow);
}
