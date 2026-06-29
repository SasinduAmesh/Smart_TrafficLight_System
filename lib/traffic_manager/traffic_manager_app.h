#ifndef TRAFFIC_MANAGER_APP_H
#define TRAFFIC_MANAGER_APP_H

#include <Arduino.h>

#include "IR_driver.h"
#include "led_driver.h"

extern TaskHandle_t traffic_manager_app_handler;

void traffic_manager_app(void *pvParameters);

#endif