#include <Arduino.h>

// Versao testada: loopback optico em um ESP32 (LED -> LDR).
// Placa: ESP32 Dev Module; Monitor Serial: 115200 baud, Newline.
// Intervalo por bit: 300 ms; limiar calibrado para a montagem com tubo.
// CRC-8: poly 0x07, init 0x00, refin=false, refout=false, xorout=0x00.

const int LED_PIN = 23;
const int LDR_PIN = 34;
const int LIMIAR = 1500;
const int TEMPO_BIT = 300;
const int MAX_CARACTERES = 60;
String entrada = "";

uint8_t calcularCRC(const String &texto) {
  uint8_t crc = 0x00;
  for (size_t i = 0; i < texto.length(); i++) {
    crc ^= (uint8_t)texto[i];
    for (int b = 0; b < 8; b++) {
      if (crc & 0x80) {
        crc = (uint8_t)((crc << 1) ^ 0x07);
      } else {
        crc = (uint8_t)(crc << 1);
      }
    }
  }
  return crc;
}

int transmitirBit(int bit) {
  digitalWrite(LED_PIN, bit ? HIGH : LOW);
  delay(TEMPO_BIT / 2);
  int leitura = analogRead(LDR_PIN);
  int recebido = leitura > LIMIAR ? 1 : 0;
  delay(TEMPO_BIT - TEMPO_BIT / 2);
  return recebido;
}

uint8_t transmitirByte(uint8_t valor) {
  uint8_t recebido = 0;
  for (int i = 7; i >= 0; i--) {
    int bit = (valor >> i) & 1;
    int bitRecebido = transmitirBit(bit);
    recebido = (uint8_t)((recebido << 1) | bitRecebido);
  }
  return recebido;
}

void imprimirHex(uint8_t valor) {
  if (valor < 16) Serial.print('0');
  Serial.print(valor, HEX);
}

void transmitirMensagem(const String &mensagem) {
  String recebida = "";
  recebida.reserve(mensagem.length());
  Serial.println();
  Serial.println("===== LI-FI COM CRC-8 =====");
  Serial.print("Mensagem enviada: ");
  Serial.println(mensagem);

  uint8_t crcEnviado = calcularCRC(mensagem);

  for (size_t i = 0; i < mensagem.length(); i++) {
    uint8_t dado = transmitirByte((uint8_t)mensagem[i]);
    recebida += (char)dado;
    Serial.print("Byte recebido: ");
    Serial.println(dado, BIN); // zeros a esquerda omitidos na exibicao
  }

  uint8_t crcRecebido = transmitirByte(crcEnviado);
  digitalWrite(LED_PIN, LOW);
  uint8_t crcCalculado = calcularCRC(recebida);

  Serial.println();
  Serial.print("Mensagem recebida: ");
  Serial.println(recebida);
  Serial.print("CRC original: 0x");
  imprimirHex(crcEnviado);
  Serial.println();
  Serial.print("CRC recebido pela luz: 0x");
  imprimirHex(crcRecebido);
  Serial.println();
  Serial.print("CRC calculado no receptor: 0x");
  imprimirHex(crcCalculado);
  Serial.println();

  if (crcRecebido == crcCalculado) {
    Serial.println("CRC OK: integridade aprovada!");
  } else {
    Serial.println("CRC ERRO: dados possivelmente corrompidos!");
  }

  if (recebida == mensagem) {
    Serial.println("Texto recebido corretamente!");
  } else {
    Serial.println("Texto recebido diferente do enviado!");
  }
  Serial.println("===========================");
  Serial.println("Digite outra mensagem:");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  analogReadResolution(12);
  entrada.reserve(MAX_CARACTERES + 1);
  Serial.println();
  Serial.println("COMUNICADOR LI-FI COM CRC-8");
  Serial.println("Velocidade: 300 ms por bit");
  Serial.println("Digite sua mensagem:");
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (entrada.length() > 0) {
        transmitirMensagem(entrada);
        entrada = "";
      }
    } else if (entrada.length() < MAX_CARACTERES) {
      entrada += c;
    }
  }
}
