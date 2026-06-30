#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include <TM1637Display.h>
#include "display_hal.h"

void initDisplays();
void showNumberDisplay_NS(int number);
void showNumberDisplay_EW(int number);

#endif