/*
  Comunicador optico educativo - loopback com UM ESP32.
  O LED envia os bits em luz; o LDR e lido fisicamente pelo ADC.
  O receptor sabe o instante dos bits porque compartilha o ESP32 transmissor.
  NAO e um enlace entre dois microcontroladores independentes.

  Conexoes:
    GPIO23 -> resistor 220/330 ohms -> anodo LED; catodo LED -> GND
    3V3 -> LDR -> (GPIO34) -> resistor 10k -> GND

  Monitor Serial: 115200 baud, termine a linha com Newline.
*/
const int PINO_LED = 23;
const int PINO_LDR = 34;
const unsigned long TEMPO_BIT_MS = 180;
const unsigned long INSTANTE_LEITURA_MS = 130;
const int CONTRASTE_MINIMO = 180; // ajuste somente a partir de testes reais

int limiar = 0;
bool luzAumentaLeitura = true;

int lerMediaLdr() {
  long soma = 0;
  for (int i = 0; i < 12; i++) {
    soma += analogRead(PINO_LDR);
    delay(2);
  }
  return (int)(soma / 12);
}

bool calibrar() {
  digitalWrite(PINO_LED, LOW);
  delay(450);
  int escuro = lerMediaLdr();
  digitalWrite(PINO_LED, HIGH);
  delay(450);
  int claro = lerMediaLdr();
  digitalWrite(PINO_LED, LOW);
  delay(200);

  int contraste = abs(claro - escuro);
  limiar = (claro + escuro) / 2;
  luzAumentaLeitura = claro > escuro;

  Serial.print("Calibracao - apagado: "); Serial.print(escuro);
  Serial.print(" / aceso: "); Serial.print(claro);
  Serial.print(" / contraste: "); Serial.print(contraste);
  Serial.print(" / limiar: "); Serial.println(limiar);

  if (contraste < CONTRASTE_MINIMO) {
    Serial.println("Contraste baixo! Aproxime e alinhe LED/LDR, use um tubo e teste de novo.");
    return false;
  }
  return true;
}

bool lerBitOptico(bool bitEnviado) {
  digitalWrite(PINO_LED, bitEnviado ? HIGH : LOW);
  delay(INSTANTE_LEITURA_MS);
  int leitura = lerMediaLdr(); // ~24 ms; amostra dentro da janela do bit
  bool bitRecebido = luzAumentaLeitura ? (leitura > limiar) : (leitura < limiar);
  unsigned long consumido = INSTANTE_LEITURA_MS + 24;
  if (TEMPO_BIT_MS > consumido) delay(TEMPO_BIT_MS - consumido);
  return bitRecebido;
}

void transmitirTexto(const String &mensagem) {
  if (!calibrar()) {
    Serial.println("Transmissao cancelada: calibre a montagem optica.");
    return;
  }

  String recebido = "";
  int errosBit = 0;
  Serial.println("Enviando bits (cada byte: MSB primeiro)...");
  for (size_t i = 0; i < mensagem.length(); i++) {
    byte original = (byte)mensagem[i];
    byte reconstruido = 0;
    for (int bit = 7; bit >= 0; bit--) {
      bool enviado = (original >> bit) & 1;
      bool recebidoBit = lerBitOptico(enviado);
      if (enviado != recebidoBit) errosBit++;
      reconstruido = (byte)((reconstruido << 1) | (recebidoBit ? 1 : 0));
      Serial.print(recebidoBit ? '1' : '0');
    }
    Serial.print(' ');
    recebido += (char)reconstruido;
  }
  digitalWrite(PINO_LED, LOW);
  Serial.println();
  Serial.print("Mensagem original:  "); Serial.println(mensagem);
  Serial.print("Mensagem recebida: "); Serial.println(recebido);
  Serial.print("Erros de bits medidos: "); Serial.println(errosBit);
  Serial.println("Digite outra frase e pressione Enter.");
}

void setup() {
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(PINO_LDR, ADC_11db);
  delay(500);
  Serial.println("Comunicador optico - 1 ESP32 / loopback fisico LED -> LDR");
  Serial.println("Digite texto curto (ex.: OLA) e envie com Newline.");
}

void loop() {
  if (Serial.available()) {
    String entrada = Serial.readStringUntil('\n');
    entrada.trim();
    if (entrada.length() > 0) transmitirTexto(entrada);
  }
}
