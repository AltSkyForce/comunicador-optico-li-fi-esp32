// Teste validado em bancada em 10/11/2026.
// ESP32: LED em GPIO23; LDR em GPIO34.
// LED conectado via resistor limitador. LDR em divisor com resistor de 10 kOhm.
// Limiar calibrado empiricamente para o conjunto com tubo de papelao.
const int LED_PIN = 23;
const int LDR_PIN = 34;
const int LIMIAR = 1500;
const int TEMPO_BIT = 1000;

void transmitirBit(int bit) {
  digitalWrite(LED_PIN, bit == 1 ? HIGH : LOW);
  delay(500); // tempo para o LDR responder

  int leitura = analogRead(LDR_PIN);
  int recebido = leitura > LIMIAR ? 1 : 0;

  Serial.print("Enviado: ");
  Serial.print(bit);
  Serial.print(" | LDR: ");
  Serial.print(leitura);
  Serial.print(" | Recebido: ");
  Serial.println(recebido);

  delay(TEMPO_BIT - 500);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  analogReadResolution(12);
  Serial.println("Teste binario com tubo iniciado!");
}

void loop() {
  transmitirBit(1);
  transmitirBit(0);
  transmitirBit(1);
  transmitirBit(1);
  transmitirBit(0);
  Serial.println("--------------------");
  digitalWrite(LED_PIN, LOW);
  delay(2000);
}
