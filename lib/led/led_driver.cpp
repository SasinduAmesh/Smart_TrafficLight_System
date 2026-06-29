#include "led_driver.h"

void all_red()
{
    digitalWrite(LED_PIN_NS_R, HIGH);
    digitalWrite(LED_PIN_NS_O, LOW);
    digitalWrite(LED_PIN_NS_G, LOW);

    digitalWrite(LED_PIN_EW_R, HIGH);
    digitalWrite(LED_PIN_EW_O, LOW);
    digitalWrite(LED_PIN_EW_G, LOW);
}

void LED_init()
{
    pinMode(LED_PIN_NS_R, OUTPUT);
    pinMode(LED_PIN_NS_O, OUTPUT);
    pinMode(LED_PIN_NS_G, OUTPUT);

    pinMode(LED_PIN_EW_R, OUTPUT);
    pinMode(LED_PIN_EW_O, OUTPUT);
    pinMode(LED_PIN_EW_G, OUTPUT);

    all_red(); // safe startup state
}

void ns_green()
{
    // NS = GREEN
    digitalWrite(LED_PIN_NS_R, LOW);
    digitalWrite(LED_PIN_NS_O, LOW);
    digitalWrite(LED_PIN_NS_G, HIGH);

    // EW = RED
    digitalWrite(LED_PIN_EW_R, HIGH);
    digitalWrite(LED_PIN_EW_O, LOW);
    digitalWrite(LED_PIN_EW_G, LOW);
}

void ew_green()
{
    // NS = RED
    digitalWrite(LED_PIN_NS_R, HIGH);
    digitalWrite(LED_PIN_NS_O, LOW);
    digitalWrite(LED_PIN_NS_G, LOW);

    // EW = GREEN
    digitalWrite(LED_PIN_EW_R, LOW);
    digitalWrite(LED_PIN_EW_O, LOW);
    digitalWrite(LED_PIN_EW_G, HIGH);
}

void ns_orange()
{
    // NS = ORANGE
    digitalWrite(LED_PIN_NS_R, LOW);
    digitalWrite(LED_PIN_NS_O, HIGH);
    digitalWrite(LED_PIN_NS_G, LOW);

    // EW = RED
    digitalWrite(LED_PIN_EW_R, HIGH);
    digitalWrite(LED_PIN_EW_O, LOW);
    digitalWrite(LED_PIN_EW_G, LOW);
}

void ew_orange()
{
    // NS = RED
    digitalWrite(LED_PIN_NS_R, HIGH);
    digitalWrite(LED_PIN_NS_O, LOW);
    digitalWrite(LED_PIN_NS_G, LOW);

    // EW = ORANGE
    digitalWrite(LED_PIN_EW_R, LOW);
    digitalWrite(LED_PIN_EW_O, HIGH);
    digitalWrite(LED_PIN_EW_G, LOW);
}

