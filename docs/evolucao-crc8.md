# Evolução do protótipo: velocidade e detecção de erros

**Atualização: 11/11/2026**

## Conquistas verificadas
1. LED de alto brilho controlado pelo GPIO23; LDR lido no GPIO34.
2. Isolamento da luz externa com tubo de papelão.
3. Transmissão de mensagens personalizadas pelo Monitor Serial.
4. Sucesso relatado a 700, 500 e 300 ms por bit.
5. CRC-8 transmitido como byte adicional pelo LED e reconstruído a partir das leituras do LDR.
6. Detecção de erro após obstrução proposital do feixe.

## Como funciona a verificação

Para os bytes originais o ESP32 calcula um CRC-8 e o transmite **depois** da mensagem. Após a recepção óptica, calcula outro CRC sobre os bytes reconstruídos e o compara ao CRC que chegou pela luz.

- Sem interferência no ensaio de `ola mundo`: `0xBE == 0xBE` → integridade aprovada.
- Com interferência: CRC recebido `0xBE`, calculado `0x84` → erro detectado.

Não existe correção automática nem retransmissão. A comparação extra entre o texto original e o recebido serve de diagnóstico, pois o mesmo ESP32 contém ambos.

## Principais parâmetros

| Parâmetro | Valor de teste |
|---|---|
| GPIO LED | 23 |
| GPIO LDR | 34 |
| Resolução ADC | 12 bits |
| Limiar de decisão | 1500 |
| Intervalo | 300 ms por bit |
| Monitor Serial | 115200 baud |
| CRC-8 | Poly 0x07, init 0x00, sem reflexão, xorout 0x00 |

## Segurança e integridade do circuito

Não usar papel-alumínio em contato com terminais. Desconectar o USB antes de mexer nos jumpers. Não conectar tensão superior a 3,3 V à entrada analógica. Buzzer passivo e sensor auxiliar **não fazem parte da versão validada**.

## Nota para apresentação

A experiência demonstra comunicação por luz visível em *loopback óptico sincronizado*, não dois microcontroladores independentes. O aluno pode demonstrar primeiro uma transmissão íntegra e depois bloquear brevemente o feixe para gerar uma falha detectável pelo CRC.
