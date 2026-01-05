# Tesla Robot - ESP32_2 (Lambalar Kontrolü)

Elektrikli araç projesi - Lambalar kontrol sistemi

> **EĞİTİM AMAÇLI PROJE** - Class kullanılmadan, basit fonksiyonlarla yazılmıştır.

## 🔧 Donanım Bağlantıları

### ESP32 Pin Bağlantıları
- **Far Lambaları**: GPIO 2
- **Stop Lambaları**: GPIO 4
- **Sinyal Lambaları (NeoPixel)**: GPIO 13
  - WS2812B LED strip
  - 16 LED toplam (8 sağ + 8 sol)
- **Nextion Ekran**:
  - GPIO 1 (TX) → Nextion RX
  - GPIO 3 (RX) → Nextion TX
  - Baud: 9600
- **MP3 Player** (başka modülde):
  - GPIO 16, GPIO 17

## ✨ Özellikler

✅ **WiFi AP+STA Mode**
- Otomatik ev WiFi'sine bağlanır
- Bağlanamazsa Access Point modu açılır
- Her yerde çalışır (ev içi/dışı)

✅ **AsyncWebServer (Yüksek Performans)**
- Asenkron HTTP server - çok hızlı!
- CORS aktif - React Native ile uyumlu
- Gerçek zamanlı durum sorgulama
- Özelleştirilebilir sinyal renkleri

✅ **Modüler Kod Yapısı**
- Class yok, sadece basit fonksiyonlar
- Her özellik ayrı dosyada
- Kolay anlaşılır ve öğrenilebilir

✅ **Nextion Ekran Desteği**
- Seri port üzerinden kontrol
- Komut bazlı protokol
- Gerçek zamanlı durum sorgulama
- HTTP ve Nextion aynı anda çalışır

## ⚙️ Kurulum

### 1. Arduino IDE Kütüphaneleri

Sketch → Include Library → Manage Libraries menüsünden yükleyin:
- `Adafruit NeoPixel` (v1.12.0+)
- `ArduinoJson` (v6.21.0+)
- `ESPAsyncWebServer` (v1.2.3+)
- `AsyncTCP` (v1.1.1+)

### 2. WiFi Ayarları

`src/config.h` dosyasını açın ve WiFi bilgilerinizi girin:

```cpp
// Ev WiFi bilgilerinizi girin
#define STA_SSID "EvWiFiAdiniz"
#define STA_PASSWORD "EvWiFiSifreniz"

// Access Point ayarları (değiştirmeyebilirsiniz)
#define AP_SSID "Tesla_Robot"
#define AP_PASSWORD "12345678"
```

### 3. ESP32'ye Yükleme

⚠️ **ÖNEMLİ**: Kod yüklerken Nextion ekranını **ÇIKARTMALISINIZ**!

GPIO1 ve GPIO3 programlama için kullanılır. Nextion bağlıyken kod yükleyemezsiniz.

1. **Nextion ekranı çıkartın**
2. Arduino IDE → Tools → Board → ESP32 Dev Module
3. Port'u seçin
4. Upload butonuna tıklayın
5. Upload bittikten sonra **Nextion'u takın**
6. Serial Monitor kullanmak istiyorsanız Nextion'u çıkartıp 9600 baud ile açın

## 📡 API Kullanımı

### Ana URL'ler

- **Ev WiFi Modu**: `http://<ESP32_IP_ADRESI>` (Serial Monitor'da gösterilir)
- **Access Point Modu**: `http://192.168.4.1`

### Endpoint'ler

#### 1. Durum Sorgulama

```http
GET /status
```

**Yanıt:**
```json
{
  "frontLamps": false,
  "brakeLamps": false,
  "signal": 0,
  "signalColor": "#FF5500"
}
```

#### 2. Far Kontrolü

```http
POST /lights/front
Content-Type: application/json

{
  "state": true
}
```

**Parametreler:**
- `state`: `true` (aç) veya `false` (kapat)

#### 3. Stop Lambası Kontrolü

```http
POST /lights/brake
Content-Type: application/json

{
  "state": true
}
```

#### 4. Sinyal Kontrolü

```http
POST /lights/signal
Content-Type: application/json

{
  "side": "left",
  "color": "#FF5500"
}
```

**Parametreler:**
- `side`:
  - `"left"` - Sol sinyal
  - `"right"` - Sağ sinyal
  - `"hazard"` - Dörtlü flaşör
  - `"off"` - Sinyal kapat
- `color`: HEX renk kodu (opsiyonel, varsayılan: `#FF5500` turuncu)

**Örnek Renkler:**
- Turuncu: `#FF5500`
- Kırmızı: `#FF0000`
- Sarı: `#FFFF00`
- Mavi: `#0000FF`

#### 5. Tüm Lambaları Kapat

```http
POST /lights/off
```

## 🖥️ Nextion Ekran Komutları

Detaylı bilgi için: [Nextion_Commands.txt](../Docs/Nextion_Commands.txt)

### Komut Listesi

```
FRONT:1              # Far aç
FRONT:0              # Far kapat
BRAKE:1              # Stop aç
BRAKE:0              # Stop kapat
SIGNAL:LEFT:FF5500   # Sol sinyal (turuncu)
SIGNAL:RIGHT:FF5500  # Sağ sinyal
SIGNAL:HAZARD:FF5500 # Dörtlü flaşör
SIGNAL:OFF           # Sinyal kapat
ALL:OFF              # Tümünü kapat
STATUS:?             # Durum sorgula
```

### Yanıt Formatı

```
OK:FRONT:ON
OK:BRAKE:OFF
OK:SIGNAL:LEFT
STATUS:FRONT:1,BRAKE:0,SIGNAL:1
ERROR:Invalid format
```

### Nextion Buton Örneği

```c
// Far butonuna basıldığında (Touch Press Event)
prints "FRONT:1",0

// Far butonu bırakıldığında (Touch Release Event)
prints "FRONT:0",0
```

## 🧪 Postman ile Test

### Test Adımları:

1. ESP32'yi başlatın ve Serial Monitor'dan IP adresini alın
2. Postman'i açın
3. Request'leri oluşturun:

**Örnek 1: Farı Aç**
```
POST http://192.168.4.1/lights/front
Body (raw, JSON):
{
  "state": true
}
```

**Örnek 2: Sol Sinyal (Kırmızı)**
```
POST http://192.168.4.1/lights/signal
Body (raw, JSON):
{
  "side": "left",
  "color": "#FF0000"
}
```

**Örnek 3: Durum Sorgula**
```
GET http://192.168.4.1/status
```

## 📁 Proje Yapısı

```
ESP32_ROBOT/
│
├── ESP32_2_Lights/                    # Ana Proje Klasörü
│   │
│   ├── ESP32_2_Lights.ino             # Arduino ana dosyası
│   ├── platformio.ini                 # PlatformIO yapılandırması
│   │
│   └── src/                           # Kaynak kodlar klasörü
│       │
│       ├── config.h                   # Pin tanımlamaları ve WiFi ayarları
│       │
│       ├── lights.h                   # Far ve Stop lambası (header)
│       ├── lights.cpp                 # Far ve Stop lambası (kod)
│       │
│       ├── neopixel_signal.h          # NeoPixel sinyal lambası (header)
│       ├── neopixel_signal.cpp        # NeoPixel sinyal lambası (kod)
│       │
│       ├── wifi_manager.h             # WiFi yönetimi (header)
│       ├── wifi_manager.cpp           # WiFi yönetimi (kod)
│       │
│       ├── web_server.h               # REST API sunucusu (header)
│       ├── web_server.cpp             # REST API sunucusu (kod)
│       │
│       ├── web_server_helpers.h       # Web server yardımcı fonksiyonlar (header)
│       ├── web_server_helpers.cpp     # Web server yardımcı fonksiyonlar (kod)
│       │
│       ├── nextion_handler.h          # Nextion ekran iletişimi (header)
│       └── nextion_handler.cpp        # Nextion ekran iletişimi (kod)
│
│
└── libraries/                         # Yeniden kullanılabilir kütüphaneler
    │
    └── WiFiManager_ESP32/             # WiFi yönetici kütüphanesi
        ├── WiFiManager_ESP32.h        # Header dosyası
        ├── WiFiManager_ESP32.cpp      # Kod dosyası
        ├── library.properties         # Kütüphane bilgileri
        └── README.md                  # Kütüphane dokümantasyonu
```

**Not:** `libraries/WiFiManager_ESP32` kütüphanesi diğer ESP32 projelerinde de kullanılabilir!

## 📚 Fonksiyon Listesi

### Lambalar Modülü (`lights.h`)

```cpp
void lights_init();              // Lambaları başlat
void front_lamps_on();           // Farı aç
void front_lamps_off();          // Farı kapat
void front_lamps_toggle();       // Farı değiştir (aç/kapat)
bool front_lamps_get_state();    // Far durumunu öğren

void brake_lamps_on();           // Stop'u aç
void brake_lamps_off();          // Stop'u kapat
void brake_lamps_toggle();       // Stop'u değiştir
bool brake_lamps_get_state();    // Stop durumunu öğren

void all_lamps_off();            // Tüm lambaları kapat
```

### NeoPixel Sinyal Modülü (`neopixel_signal.h`)

```cpp
void neopixel_init();                           // NeoPixel'i başlat
void neopixel_update();                         // Animasyonu güncelle (loop'ta çağır)

void signal_set(SignalSide side);               // Sinyal yönünü ayarla
void signal_set_with_color(SignalSide side, RGBColor color);
void signal_off();                              // Sinyali kapat

void signal_set_color(RGBColor color);          // Rengi ayarla
void signal_set_color_hex(String hexColor);     // HEX ile renk ayarla
RGBColor signal_get_color();                    // Rengi öğren

SignalSide signal_get_side();                   // Sinyal yönünü öğren

RGBColor hex_to_rgb(String hexColor);           // HEX'i RGB'ye çevir
```

### WiFi Modülü (`wifi_manager.h`)

```cpp
void wifi_init();                // WiFi'yi başlat (AP+STA)
String wifi_get_ip();            // IP adresini al
void wifi_print_info();          // Bağlantı bilgilerini göster
bool wifi_is_sta_connected();    // Ev WiFi'sine bağlı mı?
bool wifi_is_ap_enabled();       // Access Point açık mı?
```

### Web Server Modülü (`web_server.h`)

```cpp
void webserver_init();           // Sunucuyu başlat
void webserver_handle_client();  // İstekleri işle (loop'ta çağır)
```

## 🎯 Sinyal Değerleri

| Değer | Açıklama |
|-------|----------|
| `0` | SIGNAL_OFF (Kapalı) |
| `1` | SIGNAL_LEFT (Sol) |
| `2` | SIGNAL_RIGHT (Sağ) |
| `3` | SIGNAL_HAZARD (Dörtlü flaşör) |

## 🚀 Gelecek Adımlar

- [ ] Postman ile API testleri
- [ ] React Native mobil uygulama geliştirme
- [ ] Daha fazla özellik ekleme (motor, sensörler)
- [ ] ESP32_1 ile iletişim (motor kontrolü)

## 📺 YouTube & GitHub

- **YouTube**: [Kanal linkiniz]
- **GitHub**: [Repository linkiniz]

## 📄 Lisans

Açık kaynak - Kullanmakta ve değiştirmekte özgürsünüz

---

**NOT:** Bu proje eğitim amaçlıdır. Class kullanılmadan, basit fonksiyonlarla yazılmıştır.
