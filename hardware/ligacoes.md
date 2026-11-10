# Ligações elétricas — uma placa ESP32

Desligue o cabo USB **antes de inserir ou mover fios**. Confirme o rótulo dos pinos impresso na sua placa; posição pode variar entre fabricantes.

## 1. LED transmissor

```text
ESP32 GPIO 23 ── [ resistor 220 Ω ou 330 Ω ] ──►| LED ── ESP32 GND
                                                   A  K
```

- Ânodo (A): normalmente a perna **mais longa** do LED.
- Cátodo (K): normalmente a perna **mais curta** e lado achatado do encapsulamento.
- O resistor pode ficar antes ou depois do LED, desde que em série.

## 2. LDR receptor: divisor resistivo

```text
ESP32 3V3 ─── [ LDR ] ───┬─── ESP32 GPIO 34 (ADC)
                         │
                       [10 kΩ]
                         │
ESP32 GND ────────────────┘
```

- Em luz mais forte, a resistência do LDR geralmente diminui e a tensão em GPIO 34 sobe.
- GPIO 34 é **somente entrada**, apropriado para leitura analógica no ESP32 clássico.
- **Nunca aplique 5 V em GPIO 34 ou em outros GPIO do ESP32.** Use apenas 3V3 na parte sensora.
- As duas partes compartilham o GND do **mesmo** ESP32.

## Posição óptica

Aponte o LED diretamente para a face sensível do LDR, inicialmente a poucos centímetros. Um tubo de papelão pode melhorar o contraste entre aceso/apagado. Evite luz solar direta. Não há ligação elétrica entre LED e LDR: o meio de transmissão é a **luz**.

## Checklist antes de conectar USB

- [ ] Valor dos dois resistores conferido.
- [ ] LED em série com resistor; polaridade correta.
- [ ] Divisor do LDR ligado a 3V3, GPIO 34 e GND.
- [ ] Nenhum curto entre 3V3 e GND.
- [ ] Nenhum fio ligado por engano a VIN/5V.

## Limitações

Este circuito é uma demonstração de **loopback óptico com um único ESP32**. Não representa duas estações independentes e a sincronização é feita pelo próprio código que envia os bits.
