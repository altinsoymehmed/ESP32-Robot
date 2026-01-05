// ============================================
// TESLA ROBOT - ESP32_2 (LAMPS CONTROL)
// TESLA ROBOT - ESP32_2 (LAMBA KONTROLÜ)
// ============================================
//
// EN: Electric vehicle project - Lamp control module
//     Controls front lamps, brake lamps, and signal lamps (NeoPixel)
//
// TR: Elektrikli araç projesi - Lamba kontrol modülü
//     Far lambaları, stop lambaları ve sinyal lambalarını (NeoPixel) kontrol eder
//
// ============================================
// HARDWARE / DONANIM
// ============================================
// EN: - Front lamps (GPIO 2)
//     - Brake lamps (GPIO 4)
//     - Signal lamps - WS2812B NeoPixel (GPIO 13)
//       - 16 LEDs (8 right + 8 left)
//       - 500ms blink interval
//       - Color selection via Nextion display
//
// TR: - Far lambaları (GPIO 2)
//     - Stop lambaları (GPIO 4)
//     - Sinyal lambaları - WS2812B NeoPixel (GPIO 13)
//       - 16 LED (8 sağ + 8 sol)
//       - 500ms yanıp sönme
//       - Nextion ekrandan renk seçimi
//
// ============================================
// NEXTION COMMAND PROTOCOL / NEXTION KOMUT PROTOKOLü
// ============================================
// Commands from Nextion (newline terminated):
// Nextion'dan gelen komutlar (satır sonu ile biter):
//
// FRONT:1              → Turn on front lamps / Farları aç
// FRONT:0              → Turn off front lamps / Farları kapat
// BRAKE:1              → Turn on brake lamps / Stop lambalarını aç
// BRAKE:0              → Turn off brake lamps / Stop lambalarını kapat
// SIGNAL:LEFT:FF5500   → Left signal (orange) / Sol sinyal (turuncu)
// SIGNAL:RIGHT:FF5500  → Right signal (orange) / Sağ sinyal (turuncu)
// SIGNAL:HAZARD:FF5500 → Hazard lights / Dörtlü flaşör
// SIGNAL:OFF           → Turn off signal / Sinyali kapat
// ALL:OFF              → Turn off all lamps / Tüm lambaları kapat
// STATUS:?             → Request status / Durum bilgisi iste
//
// ============================================

// ============================================
// MODULE INCLUDES / MODÜL İÇE AKTARMALAR
// ============================================
// EN: Include header files from src/ folder
//     Headers contain function declarations (public API)
//     Modular design - each module handles specific functionality
//
// TR: src/ klasöründen header dosyalarını dahil et
//     Header'lar fonksiyon bildirimlerini içerir (açık API)
//     Modüler tasarım - her modül belirli bir işlevi yönetir

#include "src/config.h"            // EN: Pin definitions and constants / TR: Pin tanımlamaları ve sabitler
#include "src/lights.h"            // EN: Front and brake lamps / TR: Far ve stop lambaları
#include "src/neopixel_signal.h"   // EN: NeoPixel signal lamps / TR: NeoPixel sinyal lambaları
#include "src/nextion_handler.h"   // EN: Nextion display communication / TR: Nextion ekran iletişimi

// ============================================
// SETUP - INITIALIZATION / BAŞLATMA
// ============================================
// EN: Runs once at startup
// TR: Başlangıçta bir kez çalışır

void setup() {
  // EN: Initialize serial communication
  // TR: Seri iletişimi başlat
  Serial.begin(SERIAL_BAUD);
  delay(1000);

  // EN: Print header
  // TR: Başlık yazdır
  Serial.println("\n\n");
  Serial.println("========================================");
  Serial.println("   TESLA ROBOT - ESP32_2 (LAMBALAR)");
  Serial.println("========================================");
  Serial.println();

  // EN: Initialize lamps module (front and brake lamps)
  // TR: Lambalar modülünü başlat (far ve stop lambaları)
  lights_init();

  // EN: Initialize NeoPixel signal lamps
  // TR: NeoPixel sinyal lambalarını başlat
  neopixel_init();

  // EN: Initialize Nextion serial communication
  // TR: Nextion seri iletişimini başlat
  nextion_init();

  Serial.println("========================================");
  Serial.println("   SYSTEM READY / SISTEM HAZIR");
  Serial.println("========================================");
}

// ============================================
// LOOP - MAIN LOOP / ANA DÖNGÜ
// ============================================
// EN: Runs continuously (forever)
// TR: Sürekli çalışır (sonsuz döngü)

void loop() {
  // EN: Process commands from Nextion display
  // TR: Nextion ekrandan gelen komutları işle
  //Sürekli seri portu dinliyor. Her an bir sinyal gelebilir.
  nextion_update();

  // EN: Update NeoPixel animations (blinking)
  // TR: NeoPixel animasyonlarını güncelle (yanıp sönme)
  neopixel_update();
}
