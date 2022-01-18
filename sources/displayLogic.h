#ifndef DISPLAY_LOGIC_H
#define DISPLAY_LOGIC_H
#include <LiquidCrystal.h>

void setDisplay(LiquidCrystal* liquidCristal);
void display(const char* firstRow, const char* secondRow);

#endif
