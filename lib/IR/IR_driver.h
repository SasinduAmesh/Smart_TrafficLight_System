#ifndef IR_DRIVER_H
#define IR_DRIVER_H

#include <Arduino.h>

#include "IR_hal.h"

extern volatile int count_N1;
extern volatile int count_N2;

extern volatile int count_S1;
extern volatile int count_S2;

extern volatile int count_W1;
extern volatile int count_W2;

extern volatile int count_E1;
extern volatile int count_E2;

void IR_Init();

#endif