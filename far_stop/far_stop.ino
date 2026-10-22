// Arduino Nano D8 ve D9 pinbleri

const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 4;
const int LED4 = 5;

const unsigned long INTERVAL = 1000;  // 1 saniye
unsigned long previousMillis = 0;
bool ledState = false;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
    ledState = !ledState;

    digitalWrite(LED1, ledState);
    digitalWrite(LED2, ledState);
    digitalWrite(LED3, ledState);
    digitalWrite(LED4, ledState);
  }

  // Buraya başka işler yazabilirsin, LED'ler beklemeden yanıp sönmeye devam
  // eder.
}
