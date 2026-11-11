# Ligações usadas nos testes

## Transmissor — protoboard 1
- ESP32 **GPIO23 (D23)** → jumper preto → `b5`
- Resistor limitador do LED: `a5` ↔ `a1`
- LED de alto brilho: ânodo (+) em `d1`; cátodo (−) em `e2`
- ESP32 **GND** → jumper branco → `b2`

Caminho: GPIO23 → resistor → LED → GND.

## Receptor — protoboard 2
- LDR: `f1` ↔ `g2` (sem polaridade)
- Resistor de 10 kΩ: `j2` ↔ `j5`
- ESP32 **3V3** → jumper vermelho → `h1`
- ESP32 **GPIO34 (D34)** → jumper preto → `h2`
- ESP32 **GND** → jumper branco → `h5`

O LDR e o resistor formam um divisor de tensão: 3V3 → LDR → GPIO34 → 10 kΩ → GND.

**Observações:** mapas baseados nos furos relatados durante a montagem. Confirmar
os valores dos resistores por código de cores/multímetro antes de remontar;
não aplicar 5V aos GPIOs do ESP32; ligar/desligar USB antes de alterar conexões.
Os dois circuitos dividem a mesma placa ESP32 e o mesmo terra.
