# Roteiro de apresentação — 18/11/2026

## 1. Introdução (30–45 s)

"Nosso projeto demonstra como uma mensagem pode ser transmitida usando luz visível. Usamos um LED como transmissor e um LDR como receptor. O ESP32 controla o LED e interpreta a luminosidade medida."

## 2. Materiais e montagem (45–60 s)

Mostrar a placa ESP32, a protoboard, o LED, os resistores e o fotorresistor. Explicar o resistor de proteção do LED e o divisor resistivo do LDR.

## 3. Protocolo (45–60 s)

"Transformamos cada caractere em oito bits. O LED aceso representa 1; apagado, 0. O programa espera o sensor responder à mudança e lê a tensão do LDR."

## 4. Demonstração (1–2 min)

Digitar uma frase curta pelo Monitor Serial. Mostrar os bits transmitidos, o texto reconstruído e comparar os resultados. **Antes da apresentação, registrar uma demonstração real e repetível.**

## 5. Limitações e melhorias (30–45 s)

"Esta versão é uma transmissão óptica de laço local com um único ESP32. A comunicação depende de alinhamento e iluminação; o LDR limita a velocidade. Em versões futuras, usaríamos dois microcontroladores com sincronização independente."

## Perguntas prováveis

**Isso é Wi-Fi?** Não. Os dados passam pela luz do LED, não por ondas de rádio.

**Isso é Morse?** A ideia de modular luz lembra Morse, mas usamos codificação binária de oito bits.

**Por que só um ESP32?** Para demonstrar a conversão, a transmissão óptica e a decodificação com os componentes disponíveis. A recepção usa o sensor físico, mas a temporização é compartilhada.

**O que acontece se bloquear a luz?** Espera-se perda de bits ou falha na calibração; demonstrar somente após testar.

> Atualize este roteiro de acordo com os resultados realmente obtidos.
