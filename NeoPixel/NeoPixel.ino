#include <Adafruit_NeoPixel.h>

#define PIN_STRIP1 11
#define PIN_STRIP2 12
#define NUM_LEDS 16

Adafruit_NeoPixel strip1(NUM_LEDS, PIN_STRIP1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(NUM_LEDS, PIN_STRIP2, NEO_GRB + NEO_KHZ800);

const unsigned long INTERVAL = 1000;  // 1 saniye
unsigned long previousMillis = 0;
bool ledOn = false;

void setAll(Adafruit_NeoPixel& strip, uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void setup() {
  strip1.begin();
  strip2.begin();
  strip1.setBrightness(50);  // 0-255, güç tüketimini sınırlar
  strip2.setBrightness(50);
  strip1.clear();
  strip2.clear();
  strip1.show();
  strip2.show();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
    ledOn = !ledOn;

    uint32_t color = ledOn ? strip1.Color(0, 255, 0) : strip1.Color(0, 0, 0);
    setAll(strip1, color);
    setAll(strip2, color);
  }
}