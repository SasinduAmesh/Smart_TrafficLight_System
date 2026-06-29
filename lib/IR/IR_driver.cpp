#include "IR_driver.h"

volatile int count_N1 = 0;
volatile int count_N2 = 0;

volatile int count_S1 = 0;
volatile int count_S2 = 0;

volatile int count_W1 = 0;
volatile int count_W2 = 0;

volatile int count_E1 = 0;
volatile int count_E2 = 0;

volatile unsigned long lastTrigger_N1 = 0;
volatile unsigned long lastTrigger_N2 = 0;

volatile unsigned long lastTrigger_S1 = 0;
volatile unsigned long lastTrigger_S2 = 0;

volatile unsigned long lastTrigger_W1 = 0;
volatile unsigned long lastTrigger_W2 = 0;

volatile unsigned long lastTrigger_E1 = 0;
volatile unsigned long lastTrigger_E2 = 0;

void IR_N1_ISR()
{
    unsigned long now = millis();

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

void IR_S1_ISR()
{
    unsigned long now = millis();

    if (now - lastTrigger_S1 > 300)
    {
        if (digitalRead(IR_S1_PIN) == LOW)
        {
            count_S1++;
            lastTrigger_S1 = now;
        }
    }
}

void IR_S2_ISR()
{
    unsigned long now = millis();

    if (now - lastTrigger_S2 > 300)
    {
        if (digitalRead(IR_S2_PIN) == LOW)
        {
            count_S2++;
            lastTrigger_S2 = now;
        }
    }
}

void IR_W1_ISR()
{
    unsigned long now = millis();

    if (now - lastTrigger_W1 > 300)
    {
        if (digitalRead(IR_W1_PIN) == LOW)
        {
            count_W1++;
            lastTrigger_W1 = now;
        }
    }
}

void IR_W2_ISR()
{
    unsigned long now = millis();

    if (now - lastTrigger_W2 > 300)
    {
        if (digitalRead(IR_W2_PIN) == LOW)
        {
            count_W2++;
            lastTrigger_W2 = now;
        }
    }
}

void IR_E1_ISR()
{
    unsigned long now = millis();

    if (now - lastTrigger_E1 > 300)
    {
        if (digitalRead(IR_E1_PIN) == LOW)
        {
            count_E1++;
            lastTrigger_E1 = now;
        }
    }
}

void IR_E2_ISR()
{
    unsigned long now = millis();

    if (now - lastTrigger_E2 > 300)
    {
        if (digitalRead(IR_E2_PIN) == LOW)
        {
            count_E2++;
            lastTrigger_E2 = now;
        }
    }
}

void IR_Init()
{
    pinMode(IR_N1_PIN, INPUT_PULLUP);
    pinMode(IR_N2_PIN, INPUT_PULLUP);
    pinMode(IR_S1_PIN, INPUT_PULLUP);
    pinMode(IR_S2_PIN, INPUT_PULLUP);
    pinMode(IR_W1_PIN, INPUT_PULLUP);
    pinMode(IR_W2_PIN, INPUT_PULLUP);
    pinMode(IR_E1_PIN, INPUT_PULLUP);
    pinMode(IR_E2_PIN, INPUT_PULLUP);

    attachInterrupt(IR_N1_PIN, IR_N1_ISR, FALLING);
    attachInterrupt(IR_N2_PIN, IR_N2_ISR, FALLING);
    attachInterrupt(IR_S1_PIN, IR_S1_ISR, FALLING);
    attachInterrupt(IR_S2_PIN, IR_S2_ISR, FALLING);
    attachInterrupt(IR_W1_PIN, IR_W1_ISR, FALLING);
    attachInterrupt(IR_W2_PIN, IR_W2_ISR, FALLING);
    attachInterrupt(IR_E1_PIN, IR_E1_ISR, FALLING);
    attachInterrupt(IR_E2_PIN, IR_E2_ISR, FALLING);
}