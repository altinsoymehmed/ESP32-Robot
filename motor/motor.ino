// ESP32 + L298N: 15 saniyede yavaştan hızlıya çıkıp duran motor
// Core 2.x ve 3.x ile uyumludur.

#define M1A 33     // IN1
#define M1B 32     // IN2
#define M2A 26     // IN3
#define M2B 25     // IN4
#define PWM_PIN 3  // ENA ve ENB (ikisi birbirine bağlı)

const int PWM_FREQ = 1000;  // 1 kHz
const int PWM_RES = 8;      // 8 bit -> 0..255
const int MIN_DUTY =
    80;  // motorun dönmeye başladığı yaklaşık değer (gerekirse değiştir)
const int MAX_DUTY = 255;
const unsigned long RAMP_MS = 15000;  // 15 saniye

void pwmWrite(int duty) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(PWM_PIN, duty);
#else
  ledcWrite(0, duty);
#endif
}

void setup() {
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);

#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(PWM_PIN, PWM_FREQ, PWM_RES);
#else
  ledcSetup(0, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWM_PIN, 0);
#endif
}

void loop() {
  // İleri yön
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);

  // 15 saniyelik hızlanma
  unsigned long start = millis();
  while (true) {
    unsigned long t = millis() - start;
    if (t >= RAMP_MS) break;
    int duty = MIN_DUTY + (long)(MAX_DUTY - MIN_DUTY) * t / RAMP_MS;
    pwmWrite(duty);
    delay(20);
  }

  // Dur
  pwmWrite(0);
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);

  delay(5000);
}
