// Teste de leitura da luz do LED pelo LDR, executado em bancada.
const int LED_PIN = 23;
const int LDR_PIN = 34;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  analogReadResolution(12);
  Serial.println("Teste optico iniciado!");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  int ligado = analogRead(LDR_PIN);
  digitalWrite(LED_PIN, LOW);
  delay(500);
  int desligado = analogRead(LDR_PIN);
  Serial.print("LED ligado: ");
  Serial.print(ligado);
  Serial.print(" | LED desligado: ");
  Serial.println(desligado);
}
