#include <DSP0401B.h>

#define SDI_PIN 2   // data out
#define CLK_PIN 3   // clock
#define LE_PIN  4   // latch
#define OE_PIN  5   // output enable

DSP0401B mydisp;

void setup() {
  // 2 display chained
  mydisp.begin(2, SDI_PIN, CLK_PIN, LE_PIN, OE_PIN);
  // set brightness
  mydisp.brightness(5);
}

void loop() {
  // display 7/8 char text
  mydisp.sendtext("DISPLAY");
  delay(1000);
  // display bigger text with sliding
  mydisp.slidetext("SLIDING TEXT SO EASY",150);
  delay(1000);
}
