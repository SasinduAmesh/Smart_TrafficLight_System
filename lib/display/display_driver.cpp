#include "display_driver.h"

TM1637Display display_NS(CLK_NS, DIO_NS);
TM1637Display display_EW(CLK_EW, DIO_EW);

void initDisplays() {
  display_NS.setBrightness(7);
  display_EW.setBrightness(7);
}

void showNumberDisplay_NS(int number) {
  display_NS.showNumberDec(number, true);
}

void showNumberDisplay_EW(int number) {
  display_EW.showNumberDec(number, true);
}

void clearDisplay_NS() {
  display_NS.clear();
}

void clearDisplay_EW() {
  display_EW.clear();
}
