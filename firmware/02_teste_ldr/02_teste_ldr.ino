// Teste 02: verificar se a leitura do LDR muda com a luz.
// Circuito: 3V3 -> LDR -> GPIO34 -> resistor 10k -> GND.
const int PINO_LDR = 34;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // faixa aproximada de 0 a 4095
  analogSetPinAttenuation(PINO_LDR, ADC_11db);
  Serial.println("Teste do LDR: ilumine e depois cubra o sensor.");
}

void loop() {
  int leitura = analogRead(PINO_LDR);
  Serial.print("LDR: ");
  Serial.println(leitura);
  delay(250);
}
