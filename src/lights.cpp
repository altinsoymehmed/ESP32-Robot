/*
 * lights.cpp - Front and Brake Lamp Control Module
 *              Far ve Stop Lambası Kontrol Modülü
 *
 * EN: This module controls traditional front lamps and brake lamps
 *     using simple digital outputs (HIGH/LOW).
 *
 * TR: Bu modül geleneksel far ve stop lambalarını basit dijital
 *     çıkışlar (HIGH/LOW) kullanarak kontrol eder.
 */

#include "lights.h"

#include "config.h"

// ============================================
// static KEYWORD EXPLANATION / static AÇIKLAMASI
// ============================================
//
// EN: Variables and functions marked with 'static' are PRIVATE.
//     They can ONLY be accessed from within this file (.cpp).
//     Encapsulation principle - protects internal state.
//
// TR: 'static' ile işaretlenmiş değişken ve fonksiyonlar GİZLİDİR.
//     SADECE bu dosyadan (.cpp) erişilebilir.
//     Kapsülleme prensibi - iç durumu korur.
//
// Example / Örnek:
//   bool state = false;         → Global (herkese açık - TEHLİKELİ!)
//   static bool state = false;  → Private/Gizli (güvenli - DOĞRU!)
//
// ============================================

// ============================================
// PRIVATE VARIABLES / GİZLİ DEĞİŞKENLER (static)
// ============================================
// EN: Internal state - only accessible within this file
// TR: Dahili durum - sadece bu dosyadan erişilebilir
// Diğer dosyalarda da static bool front_state değişkeni kullansak isim çakışması olmaz.
// Lambaların durumunu görsel olarak görüyoruz. Mesaj olarak da alabilmemiz için
// front_state  ve brake_state  değişkenlerini tanımlıyoruz.
static bool front_state = false;  // Front lamp state / Far lambası durumu
static bool brake_state = false;  // Brake lamp state / Fren lambası durumu

// ============================================
// PUBLIC FUNCTIONS / AÇIK FONKSİYONLAR
// ============================================
// EN: These functions are declared in lights.h
//     and can be called from any file
// TR: Bu fonksiyonlar lights.h'de bildirilmiştir
//     ve herhangi bir dosyadan çağrılabilir

// ============================================
// INITIALIZATION / BAŞLATMA
// ============================================

/**
 * Initialize lamps (Public - DEFINITION)
 * Lambaları başlat (Açık - DEFINITION/Tanımlama)
 *
 * EN: Configures GPIO pins for front and brake lamps as outputs.
 *     Sets initial state to OFF (LOW) for both lamps.
 *     Called once during system startup from setup().
 *
 * TR: Far ve stop lambaları için GPIO pinlerini çıkış olarak yapılandırır.
 *     Her iki lamba için başlangıç durumunu KAPALI (LOW) olarak ayarlar.
 *     setup() fonksiyonundan sistem başlangıcında bir kez çağrılır.
 */
void lights_init() {
  pinMode(FRONT_LAMPS_PIN, OUTPUT);
  pinMode(BRAKE_LAMPS_PIN, OUTPUT);

  // EN: All lamps off at startup
  // TR: Başlangıçta tüm lambalar kapalı
  digitalWrite(FRONT_LAMPS_PIN, LOW);
  digitalWrite(BRAKE_LAMPS_PIN, LOW);

  Serial.println("[Lights] Lambalar hazir");
}

// ============================================
// FRONT LAMPS / FAR LAMBALARI
// ============================================

/**
 * Turn on front lamps (Public)
 * Farları aç (Açık)
 *
 * EN: Activates the front lamps by setting the GPIO pin HIGH.
 *     Updates internal state variable for tracking.
 *
 * TR: GPIO pinini HIGH yaparak farları aktif eder.
 *     İzleme için dahili durum değişkenini günceller.
 */
void front_lamps_on() {
  front_state = true;
  digitalWrite(FRONT_LAMPS_PIN, HIGH);
  Serial.println("[Lights] Far: ACIK");
}

/**
 * Turn off front lamps (Public)
 * Farları kapat (Açık)
 *
 * EN: Deactivates the front lamps by setting the GPIO pin LOW.
 *     Updates internal state variable for tracking.
 *
 * TR: GPIO pinini LOW yaparak farları deaktif eder.
 *     İzleme için dahili durum değişkenini günceller.
 */
void front_lamps_off() {
  front_state = false;
  digitalWrite(FRONT_LAMPS_PIN, LOW);
  Serial.println("[Lights] Far: KAPALI");
}

/**
 * Get front lamp state (Public)
 * Far lambası durumunu al (Açık)
 *
 * EN: Returns the current state of front lamps.
 * TR: Farların mevcut durumunu döndürür.
 *
 * @return bool - true if ON, false if OFF / AÇIK ise true, KAPALI ise false
 */
bool front_lamps_get_state() { return front_state; }

// ============================================
// BRAKE LAMPS / STOP LAMBALARI
// ============================================

/**
 * Turn on brake lamps (Public)
 * Stop lambalarını aç (Açık)
 *
 * EN: Activates the brake lamps by setting the GPIO pin HIGH.
 *     Updates internal state variable for tracking.
 *
 * TR: GPIO pinini HIGH yaparak stop lambalarını aktif eder.
 *     İzleme için dahili durum değişkenini günceller.
 */
void brake_lamps_on() {
  brake_state = true;
  digitalWrite(BRAKE_LAMPS_PIN, HIGH);
  Serial.println("[Lights] Stop: ACIK");
}

/**
 * Turn off brake lamps (Public)
 * Stop lambalarını kapat (Açık)
 *
 * EN: Deactivates the brake lamps by setting the GPIO pin LOW.
 *     Updates internal state variable for tracking.
 *
 * TR: GPIO pinini LOW yaparak stop lambalarını deaktif eder.
 *     İzleme için dahili durum değişkenini günceller.
 */
void brake_lamps_off() {
  brake_state = false;
  digitalWrite(BRAKE_LAMPS_PIN, LOW);
  Serial.println("[Lights] Stop: KAPALI");
}

/**
 * Get brake lamp state (Public)
 * Stop lambası durumunu al (Açık)
 *
 * EN: Returns the current state of brake lamps.
 * TR: Stop lambalarının mevcut durumunu döndürür.
 *
 * @return bool - true if ON, false if OFF / AÇIK ise true, KAPALI ise false
 */
bool brake_lamps_get_state() { return brake_state; }

// ============================================
// ALL LAMPS / TÜM LAMBALAR
// ============================================

/**
 * Turn off all lamps (Public)
 * Tüm lambaları kapat (Açık)
 *
 * EN: Convenience function to turn off both front and brake lamps.
 *     Calls individual lamp off functions to ensure proper state management.
 *
 * TR: Hem far hem de stop lambalarını kapatmak için kolaylık fonksiyonu.
 *     Doğru durum yönetimi için ayrı lamba kapatma fonksiyonlarını çağırır.
 */
void all_lamps_off() {
  front_lamps_off();
  brake_lamps_off();
  Serial.println("[Lights] Tum lambalar kapali");
}
