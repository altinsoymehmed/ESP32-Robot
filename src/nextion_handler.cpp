#include "nextion_handler.h"

#include "config.h"
#include "lights.h"
#include "neopixel_signal.h"

// ============================================
// static KEYWORD EXPLANATION / static AÇIKLAMASI
// ============================================
//
// EN: Variables and functions marked with 'static' are PRIVATE.
//     They can ONLY be accessed from within this file (.cpp).
//
// TR: 'static' ile işaretlenmiş değişken ve fonksiyonlar GİZLİDİR.
//     SADECE bu dosyadan (.cpp) erişilebilir.
//
// ============================================

// ============================================
// PRIVATE VARIABLES / GİZLİ DEĞİŞKENLER (static)
// ============================================
// EN: Command buffer - only accessible within this file
// TR: Komut tamponu - sadece bu dosyadan erişilebilir

static String commandBuffer = "";  // Buffer for incoming commands / Gelen komutlar için tampon

// ============================================
// NEXTION COMMAND PROTOCOL / NEXTION KOMUT PROTOKOLü
// ============================================
/*
 * EN: Commands from Nextion (terminated by newline):
 * TR: Nextion'dan gelen komutlar (satır sonu ile biter):
 *
 * FRONT:1              → Turn on front lamps / Farları aç
 * FRONT:0              → Turn off front lamps / Farları kapat
 * BRAKE:1              → Turn on brake lamps / Stop lambalarını aç
 * BRAKE:0              → Turn off brake lamps / Stop lambalarını kapat
 * SIGNAL:LEFT:FF5500   → Left signal (orange) / Sol sinyal (turuncu)
 * SIGNAL:RIGHT:FF5500  → Right signal (orange) / Sağ sinyal (turuncu)
 * SIGNAL:HAZARD:FF5500 → Hazard lights / Dörtlü flaşör
 * SIGNAL:OFF           → Turn off signal / Sinyali kapat
 * ALL:OFF              → Turn off all lamps / Tüm lambaları kapat
 * STATUS:?             → Request status / Durum bilgisi iste
 */

// ============================================
// PRIVATE HELPER FUNCTIONS / GİZLİ YARDIMCI FONKSİYONLAR (static)
// ============================================
// EN: Internal functions - not accessible from other files
// TR: İç fonksiyonlar - diğer dosyalardan erişilemez

// EN: Convert HEX string to RGB color (Private)
// TR: HEX string'i RGB rengine çevir (Gizli)
static RGBColor hex_to_color(const String& hex) {
  String clean = hex;

  // # karakterini temizle
  if (clean.startsWith("#")) {
    clean = clean.substring(1);
  }

  RGBColor color;
  // Hex'i sayıya çevir
  long number = strtol(clean.c_str(), NULL, 16);  // F = 1111  4 bit
  color.r = (number >> 16) & 0xFF;                // 0xFF5500 >> 16 = 0x0000FF, 0x0000FF & 0xFF = 0xFF = 255
  color.g = (number >> 8) & 0xFF;                 // 0xFF5500 >> 8 = 0x00FF55, 0x00FF55 & 0xFF = 0x55 = 85
  color.b = number & 0xFF;

  return color;
}

// EN: Process incoming command (Private)
// TR: Gelen komutu işle (Gizli)
static void process_command(String cmd) {
  cmd.trim();

  // EN: Exit if empty command (just Enter pressed)
  // TR: Boş komutsa çık (sadece Enter basılmış)
  if (cmd.length() == 0) return;

  // Komutu ayır
  int firstColon = cmd.indexOf(':');  //:  indexini bulur.
  if (firstColon == -1) {
    nextion_send_response("ERROR:Invalid format");
    return;
  }

  String command = cmd.substring(0, firstColon);  // ilk : noktaya kadar. FRONT
  String params = cmd.substring(firstColon + 1);  // iki noktadan bir sonra 1
  command.toUpperCase();                          // front:1 olarak da data gönderilebilir.
  params.toUpperCase();

  // FRONT komutu  FRONT:1   FRONT:0
  if (command == "FRONT") {
    if (params == "1") {
      front_lamps_on();
      nextion_send_response("OK:FRONT:ON");
    } else if (params == "0") {
      front_lamps_off();
      nextion_send_response("OK:FRONT:OFF");
    } else {
      nextion_send_response("ERROR:Invalid FRONT param");
    }
  }
  // BRAKE komutu
  else if (command == "BRAKE") {
    if (params == "1") {
      brake_lamps_on();
      nextion_send_response("OK:BRAKE:ON");
    } else if (params == "0") {
      brake_lamps_off();
      nextion_send_response("OK:BRAKE:OFF");
    } else {
      nextion_send_response("ERROR:Invalid BRAKE param");
    }
  }
  // SIGNAL komutu
  else if (command == "SIGNAL") {
    int secondColon = params.indexOf(':');

    String side = params;
    String color = "FF5500";  // Varsayılan turuncu

    if (secondColon != -1) {
      side = params.substring(0, secondColon);    // LEFT /RIGHT // HAZARD /OFF
      color = params.substring(secondColon + 1);  // #FF5500
    }

    if (side == "LEFT") {
      signal_set_with_color(SIGNAL_LEFT, hex_to_color(color));
      nextion_send_response("OK:SIGNAL:LEFT");
    } else if (side == "RIGHT") {
      signal_set_with_color(SIGNAL_RIGHT, hex_to_color(color));
      nextion_send_response("OK:SIGNAL:RIGHT");
    } else if (side == "HAZARD") {
      signal_set_with_color(SIGNAL_HAZARD, hex_to_color(color));
      nextion_send_response("OK:SIGNAL:HAZARD");
    } else if (side == "OFF") {
      signal_off();
      nextion_send_response("OK:SIGNAL:OFF");
    } else {
      nextion_send_response("ERROR:Invalid SIGNAL side");
    }
  }
  // ALL komutu
  else if (command == "ALL") {
    if (params == "OFF") {
      front_lamps_off();
      brake_lamps_off();
      signal_off();
      nextion_send_response("OK:ALL:OFF");
    } else {
      nextion_send_response("ERROR:Invalid ALL param");
    }
  }
  // STATUS komutu
  else if (command == "STATUS") {
    nextion_send_status();
  }
  // Bilinmeyen komut
  else {
    nextion_send_response("ERROR:Unknown command");
  }
}

// ============================================
// PUBLIC FUNCTIONS / AÇIK FONKSİYONLAR
// ============================================
// EN: These functions are declared in nextion_handler.h
//     and can be called from any file
// TR: Bu fonksiyonlar nextion_handler.h'de bildirilmiştir
//     ve herhangi bir dosyadan çağrılabilir

// EN: Initialize Nextion communication (Public)
// TR: Nextion iletişimini başlat (Açık)
void nextion_init() {
  // NOT: Serial0 (GPIO1/GPIO3) hem debug hem de Nextion için kullanılıyor
  // Debug mesajlarını görmek için Serial Monitor'u kapatın
  // veya Nextion bağlıyken debug mesajlarını göremezsiniz

  // Serial zaten setup()'ta başlatıldı, tekrar yapılandırma gerekmiyor
  // Sadece baud rate'i ayarlayalım
  Serial.updateBaudRate(NEXTION_BAUD);

  delay(100);

  // Nextion'a başlangıç mesajı gönder
  nextion_send_response("READY:ESP32_LIGHTS");
}

// EN: Update - read and process commands (Public)
// TR: Güncelle - komutları oku ve işle (Açık)
void nextion_update() {
  // EN: Read data from Serial if available
  // TR: Serial'den veri varsa oku
  while (Serial.available()) {
    String commandBuffer = Serial.readString();
    // EN: trim() removes whitespace from start and end
    // TR: trim() baştan ve sondan boşlukları temizler
    commandBuffer.trim();
    process_command(commandBuffer);
  }
}

// EN: Send response to Nextion (Public)
// TR: Nextion'a yanıt gönder (Açık)
void nextion_send_response(const char* message) {
  Serial.print(message);
  Serial.print("\r\n");  // Carriage return + newline
  Serial.flush();
}

// EN: Send status information (Public)
// TR: Durum bilgisini gönder (Açık)
void nextion_send_status() {
  // Lambalar durumunu gönder
  String status = "STATUS:";
  status += "FRONT:" + String(front_lamps_get_state() ? "1" : "0") + ",";
  status += "BRAKE:" + String(brake_lamps_get_state() ? "1" : "0") + ",";
  status += "SIGNAL:" + String((int)signal_get_side());

  nextion_send_response(status.c_str());
}
