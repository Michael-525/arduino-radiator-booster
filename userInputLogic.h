#ifndef USER_INPUT_LOGIC_H
#define USER_INPUT_LOGIC_H
#include <Arduino.h>

#define USER_INPUT_PIN A1

void readUserInput();
bool wasUpArrowPressed();
bool wasDownArrowPressed();
bool wasIncreaseArrowPressed();
bool wasDecreaseArrowPressed();

#endif
