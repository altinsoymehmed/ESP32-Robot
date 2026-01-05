// ============================================
// CONFIG.H - PROJECT CONFIGURATION / PROJE YAPILANDIRMASI
// ============================================
//
// EN: This file contains all hardware pin definitions and constants
//     Used across the entire project
//
// TR: Bu dosya tüm donanım pin tanımlamalarını ve sabitleri içerir
//     Tüm proje boyunca kullanılır
//
// ============================================

// ============================================
// INCLUDE GUARD / INCLUDE GUARD
// ============================================
// EN: Prevents multiple inclusion of this header file
//     #ifndef = if not defined, #define = define it
// TR: Bu header dosyasının birden fazla dahil edilmesini önler
//     #ifndef = tanımlı değilse, #define = tanımla

#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// PIN DEFINITIONS / PIN TANIMLARI
// ============================================
// EN: GPIO pin assignments for lamps
// TR: Lambalar için GPIO pin atamaları

const int FRONT_LAMPS_PIN = 2;    // GPIO2 - Front lamps / Farlar
const int BRAKE_LAMPS_PIN = 4;    // GPIO4 - Brake lamps / Stop lambaları
const int NEOPIXEL_PIN = 13;      // GPIO13 - NeoPixel LED strip / NeoPixel LED şerit

// ============================================
// NEOPIXEL SETTINGS / NEOPIXEL AYARLARI
// ============================================
// EN: NeoPixel LED strip configuration
// TR: NeoPixel LED şerit yapılandırması

const int NEOPIXEL_COUNT = 16;          // EN: Total LEDs (8 right + 8 left) / TR: Toplam LED (8 sağ + 8 sol)
const int NEOPIXEL_RIGHT_START = 0;     // EN: Right signal start index / TR: Sağ sinyal başlangıç indexi
const int NEOPIXEL_RIGHT_END = 7;       // EN: Right signal end index / TR: Sağ sinyal bitiş indexi
const int NEOPIXEL_LEFT_START = 8;      // EN: Left signal start index / TR: Sol sinyal başlangıç indexi
const int NEOPIXEL_LEFT_END = 15;       // EN: Left signal end index / TR: Sol sinyal bitiş indexi

const int SIGNAL_BLINK_INTERVAL = 500;  // EN: 500ms blink interval / TR: 500ms yanıp sönme aralığı

// ============================================
// SERIAL PORT SETTINGS / SERİ PORT AYARLARI
// ============================================
// EN: Serial communication settings
//     Serial (GPIO1/GPIO3) used for Nextion display
//     115200 for debugging (during upload)
//     9600 for Nextion (during operation)
//
// TR: Seri iletişim ayarları
//     Serial (GPIO1/GPIO3) Nextion ekran için kullanılır
//     115200 debug için (kod yüklerken)
//     9600 Nextion için (çalışırken)

const int SERIAL_BAUD = 115200;   // EN: Debug baud rate / TR: Debug baud hızı
const int NEXTION_BAUD = 9600;    // EN: Nextion baud rate / TR: Nextion baud hızı

#endif  // CONFIG_H
