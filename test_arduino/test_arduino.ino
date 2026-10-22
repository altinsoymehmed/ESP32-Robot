#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

#define PIN_STRIP1 11
#define PIN_STRIP2 12
#define NUM_LEDS 16
// Arduino Nano D8 ve D9 pinbleri

const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 4;
const int LED4 = 5;

//

Adafruit_NeoPixel strip1(NUM_LEDS, PIN_STRIP1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(NUM_LEDS, PIN_STRIP2, NEO_GRB + NEO_KHZ800);
// Adres genelde 0x27, bazı modüllerde 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setAll(Adafruit_NeoPixel& strip, uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void setup() {
  // LEDS
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);

  // NepPixel

  strip1.begin();
  strip2.begin();
  strip1.setBrightness(50);  // 0-255, güç tüketimini sınırlar
  strip2.setBrightness(50);
  strip1.clear();
  strip2.clear();
  strip1.show();
  strip2.show();
  setAll(strip1, strip1.Color(255, 0, 0));
  setAll(strip2, strip2.Color(255, 0, 0));

  // Adres genelde 0x27, bazı modüllerde 0x3F
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ESP32 Robot!");
}
void loop() {
  // Buraya başka işler yazabilirsin, LED'ler beklemeden yanıp sönmeye devam
  // eder.
}