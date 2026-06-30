#include <Arduino.h>

#include "traffic_manager_app.h"

void setup()
{
    Serial.begin(115200);

    xTaskCreatePinnedToCore(traffic_manager_app, "traffic_manager_app", 8192, NULL, 1, &traffic_manager_app_handler, 1);
}

void loop()
{
}


/*
#include <Arduino.h>

#define IR_N1_PIN 22
#define IR_N2_PIN 23

int count_N1 = 0;
int count_N2 = 0;
int total_count_N = 0;

volatile unsigned long lastTrigger_N1 = 0;
volatile unsigned long lastTrigger_N2 = 0;

void IR_N1_ISR()
{
    unsigned long now = millis();

    // only count falling edge with time lock
    if (now - lastTrigger_N1 > 300)
    {
        if (digitalRead(IR_N1_PIN) == LOW)
        {
            count_N1++;
            lastTrigger_N1 = now;
        }
    }
}

void IR_N2_ISR()
{
    unsigned long now = millis();

    if (now - lastTrigger_N2 > 300)
    {
        if (digitalRead(IR_N2_PIN) == LOW)
        {
            count_N2++;
            lastTrigger_N2 = now;
        }
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(IR_N1_PIN, INPUT_PULLUP);
    pinMode(IR_N2_PIN, INPUT_PULLUP);

    attachInterrupt(IR_N1_PIN, IR_N1_ISR, FALLING);
    attachInterrupt(IR_N2_PIN, IR_N2_ISR, FALLING);
}

void loop()
{
    Serial.print("Count1: ");
    Serial.print(count_N1);
    Serial.print(" | Count2: ");
    Serial.print(count_N2);
    Serial.print(" | No. of vehicles in N: ");

    total_count_N = count_N2 - count_N1;
    if (total_count_N < 0)
    {
        total_count_N = 0;
    }

    Serial.println(total_count_N);
    delay(500);
}
*/

/*
#include <Arduino.h>
#include "IR_driver.h"

int total_count_N = 0;

void setup()
{
    Serial.begin(115200);

    IR_Init();
}

void loop()
{
    Serial.print("Count1: ");
    Serial.print(count_N1);

    Serial.print(" | Count2: ");
    Serial.print(count_N2);

    Serial.print(" | No. of vehicles in N: ");

    total_count_N = count_N2 - count_N1;

    if (total_count_N < 0)
    {
        total_count_N = 0;
    }

    Serial.println(total_count_N);

    delay(500);
}
*/