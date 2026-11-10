// Teste 01: piscar o LED externo no GPIO 23.
// Circuito: GPIO 23 -> resistor 220/330 ohms -> anodo LED; catodo -> GND.
const int PINO_LED = 23;

void setup() {
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);
}

void loop() {
  digitalWrite(PINO_LED, HIGH);
  delay(500);
  digitalWrite(PINO_LED, LOW);
  delay(500);
}
