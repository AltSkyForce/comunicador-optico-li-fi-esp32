# Registro de testes — 10/11/2026

> Valores transcritos de capturas do Monitor Serial do experimento.
> São leituras ADC de 12 bits (0–4095), não medições de lux.

| Etapa | Condição | Observação | Resultado |
| --- | --- | --- | --- |
| 1 | Upload ESP32 Dev Module via COM5 | Gravação verificada e mensagens a 115200 baud | Aprovado |
| 2 | LED alto brilho no GPIO23 | Pisca alternando ligado/desligado | Aprovado |
| 3 | LDR no GPIO34, luz ambiente | Aproximadamente 2060 | Aprovado |
| 3 | LDR coberto com a mão | 0 a 48 | Aprovado |
| 3 | LDR iluminado com lanterna do celular | Próximo de 4095 (saturação da leitura) | Aprovado |
| 4 | LED e LDR alinhados sem tubo | Ligado ~3270 / desligado ~1900 | Aprovado |
| 5 | LED e LDR alinhados com tubo | Desligado 0 / ligado tipicamente ~2850–2915 | Aprovado |
| 6 | Sequência binária `10110` com tubo | Enviado = recebido em várias repetições observadas, limiar 1500 | Aprovado no teste observado |
| 7 | Texto completo (bytes, palavras) | Ainda não executado | Pendente |
| 8 | Buzzer passivo | Disponível; ligação e especificações ainda não verificadas | Pendente |

## Interpretação

O tubo reduz a interferência luminosa ambiental: o LED apagado passou de aproximadamente 1900 para 0.
A amplitude de leitura **não aumentou necessariamente**: o LED ligado ficou tipicamente em ~2850–2915,
abaixo de ~3270 sem tubo. O principal ganho observado foi o contraste e o isolamento do sinal.

O limiar de 1500 funcionou para a montagem específica com o tubo. Ele não é universal: deve ser
recalibrado se a posição, o LED, o LDR ou a iluminação mudarem.

A sequência `10110` foi produzida e amostrada pelo **mesmo ESP32**, que controla os instantes
de leitura; trata-se de um teste de loopback óptico, não de dois dispositivos independentes.

## Próximos testes

- Transmitir e reconstruir caracteres a partir de leituras do LDR.
- Testar diferentes alinhamentos, iluminação e velocidades.
- Registrar fotos e repetir medições para obter uma taxa de erro quantitativa.
- Adicionar buzzer passivo somente após conferir tensão, corrente e tipo do transdutor.
