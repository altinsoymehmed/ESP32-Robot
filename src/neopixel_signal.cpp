#include "neopixel_signal.h"

#include <Adafruit_NeoPixel.h>

#include "config.h"

// ============================================
// static KEYWORD EXPLANATION / static AÇIKLAMASI
// ============================================
//
// EN: Variables and functions marked with 'static' are PRIVATE.
//     They can ONLY be accessed from within this file (.cpp).
//     To access from other files, remove 'static' and declare in header (.h).
//
// TR: 'static' ile işaretlenmiş değişken ve fonksiyonlar GİZLİDİR.
//     SADECE bu dosyadan (.cpp) erişilebilir.
//     Dışarıdan erişmek için 'static' kaldırılmalı ve header'da (.h)
//     bildirilmelidir.
//
// Example / Örnek:
//   static void helper()  → Private/Gizli (only this file / sadece bu dosya)
//   void signal_set()     → Public/Açık (declared in .h / .h'de bildirilmiş)
//
// ============================================

// ============================================
// PRIVATE VARIABLES / GİZLİ DEĞİŞKENLER (static)
// ============================================
// EN: These variables are only accessible within this file
// TR: Bu değişkenler sadece bu dosya içinden erişilebilir

// NeoPixel LED strip object / NeoPixel LED şerit nesnesi
static Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Internal state variables / Dahili durum değişkenleri
static SignalSide current_side = SIGNAL_OFF;
static RGBColor current_color = {255, 85, 0};  // Default: Orange / Varsayılan: Turuncu
static unsigned long last_blink_time = 0;
static bool blink_state = false;

// ============================================
// HELPER FUNCTIONS / YARDIMCI FONKSİYONLAR
// ============================================

// EN: Convert HEX string to RGB color (Public - declared in .h)
// TR: HEX string'i RGB rengine çevir (Açık - .h'de bildirilmiş)
RGBColor hex_to_rgb(String hexColor) {
  RGBColor color;

  // # işaretini kaldır
  if (hexColor.startsWith("#")) {
    hexColor = hexColor.substring(1);
  }

  // Geçersiz format kontrolü
  if (hexColor.length() != 6) {
    color.r = 255;
    color.g = 85;
    color.b = 0;
    return color;  // Varsayılan turuncu
  }

  // Hex'ten sayıya çevir
  long number = strtol(hexColor.c_str(), NULL, 16);
  color.r = (number >> 16) & 0xFF;
  color.g = (number >> 8) & 0xFF;
  color.b = number & 0xFF;

  return color;
}

// ============================================
// PRIVATE HELPER FUNCTIONS / GİZLİ YARDIMCI FONKSİYONLAR (static)
// ============================================
// EN: Internal functions - not accessible from other files
// TR: İç fonksiyonlar - diğer dosyalardan erişilemez

// EN: Clear all LEDs (Private)
// TR: Tüm LED'leri temizle (Gizli)
// Diğer dosyalarda da static void clear_all_leds() fonksiyonu  kullansak isim çakışması olmaz.
static void clear_all_leds() {
  strip.clear();
  strip.show();
}

// EN: Turn on left signal LEDs (Private)
// TR: Sol sinyal LED'lerini yak (Gizli)
static void turn_on_right() {
  uint32_t color = strip.Color(current_color.r, current_color.g, current_color.b);
  for (int i = NEOPIXEL_LEFT_START; i <= NEOPIXEL_LEFT_END; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

// EN: Turn on right signal LEDs (Private)
// TR: Sağ sinyal LED'lerini yak (Gizli)
static void turn_on_left() {
  uint32_t color = strip.Color(current_color.r, current_color.g, current_color.b);
  for (int i = NEOPIXEL_RIGHT_START; i <= NEOPIXEL_RIGHT_END; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

// EN: Turn on both sides - hazard lights (Private)
// TR: Her iki tarafı da yak - dörtlü flaşör (Gizli)
static void turn_on_hazard() {
  turn_on_left();
  turn_on_right();
}

// ============================================
// PUBLIC FUNCTIONS / AÇIK FONKSİYONLAR
// ============================================
// EN: These functions are declared in neopixel_signal.h
//     and can be called from any file
// TR: Bu fonksiyonlar neopixel_signal.h'de bildirilmiştir
//     ve herhangi bir dosyadan çağrılabilir

// EN: Initialize NeoPixel (Public)
// TR: NeoPixel'i başlat (Açık)
void neopixel_init() {
  strip.begin();
  strip.setBrightness(255);
  strip.show();  // Tüm LED'ler kapalı

  Serial.println("[NeoPixel] Sinyal lambalari hazir");
}

// EN: Update signal blinking (call in loop) (Public)
// TR: Sinyal yanıp sönmesini güncelle (loop'ta çağır) (Açık)
void neopixel_update() {
  // Sinyal kapalıysa hiçbir şey yapma
  // loop'da sürekli çalışıyor. Bu fonksiyonu
  // komple çalıştırmaması için

  if (current_side == SIGNAL_OFF) {
    return;
  }

  // Yanıp sönme zamanı kontrolü
  unsigned long current_time = millis();
  if (current_time - last_blink_time >= SIGNAL_BLINK_INTERVAL) {
    last_blink_time = current_time;
    blink_state = !blink_state;  // Durumu değiştir

    if (blink_state) {
      // LED'leri yak
      switch (current_side) {
        case SIGNAL_LEFT:
          turn_on_left();
          break;
        case SIGNAL_RIGHT:
          turn_on_right();
          break;
        case SIGNAL_HAZARD:
          turn_on_hazard();
          break;
        default:
          break;
      }
    } else {
      // LED'leri söndür
      clear_all_leds();
    }
  }
}

// EN: Set signal side (Public)
// TR: Sinyal yönünü ayarla (Açık)
void signal_set(SignalSide side) {
  current_side = side;
  blink_state = false;
  last_blink_time = millis();

  // Sinyal kapalıysa LED'leri temizle
  if (side == SIGNAL_OFF) {
    clear_all_leds();
  }

  Serial.printf("[NeoPixel] Sinyal: %d\n", side);
}

// EN: Set signal side with custom color (Public)
// TR: Sinyal yönünü özel renk ile ayarla (Açık)
void signal_set_with_color(SignalSide side, RGBColor color) {
  current_color = color;
  signal_set(side);
  Serial.printf("[NeoPixel] Renk: #%02X%02X%02X\n", color.r, color.g, color.b);
}

// EN: Turn off signal (Public)
// TR: Sinyali kapat (Açık)
void signal_off() { signal_set(SIGNAL_OFF); }

// EN: Set signal color (RGB) (Public)
// TR: Sinyal rengini ayarla (RGB) (Açık)
void signal_set_color(RGBColor color) {
  current_color = color;
  Serial.printf("[NeoPixel] Renk degisti: #%02X%02X%02X\n", color.r, color.g, color.b);
}

// EN: Set signal color (HEX string) (Public)
// TR: Sinyal rengini ayarla (HEX string) (Açık)
void signal_set_color_hex(String hexColor) {
  RGBColor color = hex_to_rgb(hexColor);
  signal_set_color(color);
}

// EN: Get current signal color (Public)
// TR: Mevcut sinyal rengini al (Açık)
RGBColor signal_get_color() { return current_color; }

// EN: Get current signal side (Public)
// TR: Mevcut sinyal yönünü al (Açık)
SignalSide signal_get_side() { return current_side; }
