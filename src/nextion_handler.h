/*
 * nextion_handler.h - Nextion Display Communication Module Interface
 *                     Nextion Ekran İletişim Modülü Arayüzü
 *
 * EN: This header file defines the public interface for communicating with
 *     Nextion touchscreen displays via serial protocol. Handles command
 *     reception, parsing, and status updates to the display.
 *
 * TR: Bu header dosyası, Nextion dokunmatik ekranlarla seri protokol
 *     üzerinden iletişim kurmak için genel arayüzü tanımlar. Komut alımı,
 *     ayrıştırma ve ekrana durum güncellemeleri işler.
 */

#ifndef NEXTION_HANDLER_H
#define NEXTION_HANDLER_H

#include <Arduino.h>

// ============================================
// NEXTION HANDLER FUNCTIONS
// NEXTION HANDLER FONKSİYONLARI
// ============================================

// ============================================
// INITIALIZATION / BAŞLATMA
// ============================================

// EN: Initialize Nextion serial port communication
// TR: Nextion seri port iletişimini başlat
void nextion_init();

// ============================================
// COMMAND PROCESSING / KOMUT İŞLEME
// ============================================

// EN: Read and process incoming commands from Nextion display
//     Must be called continuously in loop() to handle user input
// TR: Nextion ekranından gelen komutları oku ve işle
//     Kullanıcı girişini işlemek için loop() içinde sürekli çağrılmalı
void nextion_update();

// ============================================
// COMMUNICATION / İLETİŞİM
// ============================================

// EN: Send a response message to Nextion display
// TR: Nextion ekranına yanıt mesajı gönder
//Arduino String kullanmıyor, sadece basit const char* kullanıyor. 
//Bu daha performanslı bir yaklaşım.
void nextion_send_response(const char* message);

// EN: Send current system status information to Nextion display
//     Updates lamp states, colors, and other status indicators
// TR: Nextion ekranına mevcut sistem durum bilgisini gönder
//     Lamba durumlarını, renkleri ve diğer durum göstergelerini günceller
void nextion_send_status();

#endif // NEXTION_HANDLER_H
