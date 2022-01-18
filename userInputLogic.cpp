#include "userInputLogic.h"

bool _upArrowInputPressed = false;
bool _upArrowInputPressedIgnore = false;
bool _downArrowInputPressed = false;
bool _downArrowInputPressedIgnore = false;
bool _increaseArrowInputPressed = false;
bool _increaseArrowInputPressedIgnore = false;
bool _decreaseArrowInputPressed = false;
bool _decreaseArrowInputPressedIgnore = false;



/*
 * IF a button range is triggered / pressed 
 *  THEN mark Button as pressed 
 *  AND mark button as Ignored.
 * 
 *  THEN IF button is still pressed in next cycle, 
 *    THEN ignore it (ignore flag is set)
 * 
 * IF no button is pressed
 *  THEN clear ignored list
 * 
 * IF button check is called
 *  THEN mark button as nonPressed so the function always expect a 
 *    true once per user interaction and not per cycle.
 */
void readUserInput() {

  int inputReadValue = analogRead(USER_INPUT_PIN);
  // Note: The ranges need to be modified depending on wirelengh and resistor values.
  switch(inputReadValue){
    case 910 ... 930:
      if(_upArrowInputPressedIgnore) {break;}
      _upArrowInputPressed = _upArrowInputPressedIgnore = true;
      break;
    case 940 ... 970:
      if(_downArrowInputPressedIgnore) {break;}
      _downArrowInputPressed = _downArrowInputPressedIgnore = true;
      break;
   case 980 ... 1008:
      if(_decreaseArrowInputPressedIgnore) {break;}
      _decreaseArrowInputPressed = _decreaseArrowInputPressedIgnore = true;
      Serial.println(inputReadValue);
      break;
   case 1009 ... 1023:
      if(_increaseArrowInputPressedIgnore) {break;}
      _increaseArrowInputPressed = _increaseArrowInputPressedIgnore = true;
      Serial.println(inputReadValue);
      break;
   case 0 ... 10:
      // Allowing to recheck if a new button is pressed. This will force that
      // only the user interaction is counted once per press and not per cycle.
      _upArrowInputPressedIgnore = 
      _downArrowInputPressedIgnore =
      _decreaseArrowInputPressedIgnore =
      _increaseArrowInputPressedIgnore = false;
      break;
    default:
      Serial.print("Out of range ");
      Serial.println(inputReadValue);
      break;
  }  
}

bool wasUpArrowPressed() {
  if (_upArrowInputPressed){
    _upArrowInputPressed = false;
    return true;
  }
  return _upArrowInputPressed;
}

bool wasDownArrowPressed() {
    if (_downArrowInputPressed){
    _downArrowInputPressed = false;
    return true;
  }
  return _downArrowInputPressed;
}

bool wasIncreaseArrowPressed() {
    if (_increaseArrowInputPressed){
    _increaseArrowInputPressed = false;
    return true;
  }
  return _increaseArrowInputPressed;
}

bool wasDecreaseArrowPressed() {
    if (_decreaseArrowInputPressed){
    _decreaseArrowInputPressed = false;
    return true;
  }
  return _decreaseArrowInputPressed;
}
