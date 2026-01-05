
/*
 * lights.h - Module Interface / Modül Arayüzü
 *
 * EN: This header file defines the public interface of the lights module.
 *     Only functions declared here can be called from other files.
 *     Static functions in lights.cpp remain private within the module.
 *
 * TR: Bu header dosyası, lights modülünün dışarıya açık fonksiyonlarını tanımlar.
 *     Sadece burada bildirilen fonksiyonlar diğer dosyalardan çağrılabilir.
 *     lights.cpp içindeki static fonksiyonlar modül içinde gizli kalır (private).
 *
 * INCLUDE GUARD / KORUMA
 * #########################
 * #ifndef LIGHTS_H
 * #define LIGHTS_H
 *
 * EN: Written in uppercase matching the filename. #ifndef LIGHTS_H checks if
 *     undefined, then #define LIGHTS_H defines it. This prevents the same
 *     header file from being included multiple times in a project.
 *
 * TR: Dosya adı ile aynı olarak büyük harfler ile yazılır. #ifndef LIGHTS_H
 *     tanımsız ise tanımla. Aynı header dosyasının bir projede birden fazla
 *     kez dahil edilmesini önler.
 * ##############################
 */

#ifndef LIGHTS_H
#define LIGHTS_H

#include <Arduino.h>

// ============================================
// FRONT AND BRAKE LAMP FUNCTIONS
// FAR VE STOP LAMBASI FONKSİYONLARI
// ============================================

// EN: Initialization function - called in setup()
// TR: Başlatma fonksiyonu - setup() içinde çağrılır
void lights_init();  // DECLARATION (Bildirim)

// EN: Front lamp control
// TR: Far kontrolü
void front_lamps_on();   // DECLARATION - Turn on front lamps / Farları aç
void front_lamps_off();  // DECLARATION - Turn off front lamps / Farları kapat
bool front_lamps_get_state();  // DECLARATION - Get front lamp state / Far durumunu al

// EN: Brake lamp control
// TR: Stop lambası kontrolü
void brake_lamps_on();   // DECLARATION - Turn on brake lamps / Stop lambalarını aç
void brake_lamps_off();  // DECLARATION - Turn off brake lamps / Stop lambalarını kapat
bool brake_lamps_get_state();  // DECLARATION - Get brake lamp state / Stop durumunu al

// EN: Turn off all lamps
// TR: Tüm lambaları kapat
void all_lamps_off();

#endif  // LIGHTS_H
