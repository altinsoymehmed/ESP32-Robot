/*
 * neopixel_signal.h - NeoPixel Signal Lamp Module Interface
 *                     NeoPixel Sinyal Lambası Modül Arayüzü
 *
 * EN: This header file defines the public interface for controlling
 *     WS2812B/WS2811 NeoPixel LED strips as signal/turn indicator lamps.
 *     Supports left, right, hazard modes with customizable RGB colors.
 *
 * TR: Bu header dosyası, WS2812B/WS2811 NeoPixel LED şeritleri sinyal/
 *     gösterge lambaları olarak kontrol etmek için genel arayüzü tanımlar.
 *     Özelleştirilebilir RGB renklerle sol, sağ, dörtlü flaşör modlarını destekler.
 */
#ifndef NEOPIXEL_SIGNAL_H
#define NEOPIXEL_SIGNAL_H

#include <Arduino.h>

// ============================================
// SIGNAL LAMP (NEOPIXEL) FUNCTIONS
// SİNYAL LAMBASI (NEOPIXEL) FONKSİYONLARI
// ============================================

/**
 * Signal Direction Enumeration
 * Sinyal Yönü Numaralandırması
 *
 * EN: Defines the possible signal lamp states.
 * TR: Sinyal lambası durumlarını tanımlar.
 * Kodun okunabilinirliğini arttırabilmek için enum  kullanıyoruz.SIGNAL_OFF = 0, 
 * biz SIGNAL_OFF olarak algılıyoruz. Bilgisayar 0 olarak algılıyor.
 * Tip güvenliği: Enum sayesinde hatalı değerler verilmesini engelliyoruz
 */
enum SignalSide {
  SIGNAL_OFF = 0,    // EN: All signals off / TR: Tüm sinyaller kapalı
  SIGNAL_LEFT = 1,   // EN: Left turn signal / TR: Sol sinyal
  SIGNAL_RIGHT = 2,  // EN: Right turn signal / TR: Sağ sinyal
  SIGNAL_HAZARD = 3  // EN: Hazard lights (both sides) / TR: Dörtlü flaşör (her iki taraf)
};

/**
 * RGB Color Structure
 * RGB Renk Yapısı
 *
 * EN: Defines a color using Red, Green, Blue components (0-255 each).
 * TR: Kırmızı, Yeşil, Mavi bileşenleri kullanarak bir renk tanımlar (her biri 0-255).
 * Renk değişkenlerini bir arada struct yapısı altında bir bütün olarak tanımlıyoruz.
 */
struct RGBColor {
  uint8_t r;  // EN: Red (0-255) / TR: Kırmızı (0-255)
  uint8_t g;  // EN: Green (0-255) / TR: Yeşil (0-255)
  uint8_t b;  // EN: Blue (0-255) / TR: Mavi (0-255)
};

// ============================================
// INITIALIZATION AND UPDATE / BAŞLATMA VE GÜNCELLEME
// ============================================

/**
 * EN: Public functions that can be called from other modules.
 * TR: Dışa açık yani diğer modüllerden kullanabileceğimiz fonksiyonlar.
 */

// EN: Initialization - called in setup()
// TR: Başlatma - setup() içinde çağrılır
void neopixel_init();

// EN: Must be called continuously in loop() for blinking effect
// TR: Loop içinde sürekli çağrılmalı (yanıp sönme efekti için)
void neopixel_update();

// ============================================
// SIGNAL CONTROL / SİNYAL KONTROLÜ
// ============================================

// EN: Set signal direction (uses current color)
// TR: Sinyal yönünü ayarla (mevcut rengi kullanır)
void signal_set(SignalSide side);

// EN: Set signal direction with specific color
// TR: Belirli bir renkle sinyal yönünü ayarla
void signal_set_with_color(SignalSide side, RGBColor color);

// EN: Turn off all signals
// TR: Tüm sinyalleri kapat
void signal_off();

// ============================================
// COLOR SETTINGS / RENK AYARLARI
// ============================================

// EN: Set signal color (RGB structure)
// TR: Sinyal rengini ayarla (RGB yapısı)
void signal_set_color(RGBColor color);

// EN: Set signal color from HEX string (e.g., "#FF5500")
// TR: HEX string'den sinyal rengini ayarla (örnek: "#FF5500")
void signal_set_color_hex(String hexColor);

// EN: Get current signal color
// TR: Mevcut sinyal rengini al
RGBColor signal_get_color();

// ============================================
// STATE QUERY / DURUM SORGULAMA
// ============================================

// EN: Get current signal direction/side
// TR: Mevcut sinyal yönünü/tarafını al
SignalSide signal_get_side();

// ============================================
// UTILITY FUNCTIONS / YARDIMCI FONKSİYONLAR
// ============================================

// EN: Helper function - Convert HEX string to RGB color
// TR: Yardımcı fonksiyon - HEX string'i RGB renge dönüştür
RGBColor hex_to_rgb(String hexColor);

#endif  // NEOPIXEL_SIGNAL_H
