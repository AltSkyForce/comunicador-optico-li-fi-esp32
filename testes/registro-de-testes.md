# Registro experimental — Comunicador óptico Li-Fi

As leituras são valores ADC de 12 bits (0–4095), **não valores de iluminância em lux**. Os resultados abaixo vêm dos testes e capturas do Monitor Serial apresentados durante a montagem.

## Transmissão e recepção iniciais — 10/11/2026

| Etapa | Observação |
|---|---|
| ESP32 programado via Arduino IDE | Gravação e comunicação serial aprovadas |
| LED de alto brilho no GPIO23 | Pisca de acordo com o código |
| LDR no GPIO34 | Coberto: 0–48; ambiente: ~2060; lanterna: até 4095 |
| LED/LDR sem tubo | LED ligado ~3270; apagado ~1900 |
| LED/LDR com tubo | LED ligado tipicamente ~2850–2915; apagado 0 |
| Bits `10110` | Recepção correta nas repetições observadas |
| Palavra `OLA` | Recuperada por leituras do LDR |
| Mensagens personalizadas | `Guilherme` e `ola mundo` recuperadas |

### Problema identificado: alumínio perto das conexões

Foi colocado papel-alumínio em volta do tubo, e houve leituras elevadas mesmo com o LED apagado. Após a retirada do alumínio, o sistema voltou a funcionar normalmente. O contato elétrico com o material condutor foi a causa **suspeita, compatível com o comportamento observado**, mas não medida com instrumento. Evitar materiais condutores em contato com fios e terminais.

## Velocidade — 11/11/2026

Mensagem de teste: `ola mundo` = 9 caracteres = 72 bits de dados.

| Duração do bit | Taxa bruta teórica | Duração apenas dos 72 bits | Resultado informado |
|---|---:|---:|---|
| 1000 ms | 1 bit/s | 72,0 s | Funcionou inicialmente |
| 700 ms | ~1,43 bit/s | 50,4 s | Sucesso |
| 500 ms | 2 bit/s | 36,0 s | Sucesso |
| 300 ms | ~3,33 bit/s | 21,6 s | Sucesso |

Os tempos não incluem overhead nem CRC. **Não se determinou a velocidade máxima física do receptor.** Também não há ensaio estatístico de taxa de erro para todas as velocidades.

## Verificação CRC-8 — 11/11/2026

Parâmetros: polinômio `0x07`, valor inicial `0x00`, sem reflexão, XOR final `0x00`. Mensagem `ola mundo`, sem acentos.

### Ensaio sem obstáculo

```text
Mensagem enviada: ola mundo
Mensagem recebida: ola mundo
CRC original: 0xBE
CRC recebido pela luz: 0xBE
CRC calculado no receptor: 0xBE
CRC OK: integridade aprovada!
Texto recebido corretamente!
```

### Ensaio com obstrução temporária da luz

```text
Mensagem enviada: ola mundo
Mensagem recebida: [texto alterado]
CRC original: 0xBE
CRC recebido pela luz: 0xBE
CRC calculado no receptor: 0x84
CRC ERRO: dados possivelmente corrompidos!
Texto recebido diferente do enviado!
```

A obstrução interrompeu parte da informação óptica, corrompendo a mensagem; o CRC-8 **detectou esse erro observado**.

### Limitações metodológicas

- O sistema é um loopback sincronizado **no mesmo ESP32**: a leitura do LDR ocorre nos instantes controlados pelo transmissor.
- O CRC é enviado como um byte adicional pelo LED e lido pelo LDR, mas comprimento e sincronismo são conhecidos localmente.
- CRC-8 detecta muitos, mas não todos, os possíveis erros; pode haver colisões.
- O teste com obstrução mostra **detecção**, não **correção** nem retransmissão.

## Experimentos recomendados

- Fazer 10 ou mais repetições por velocidade e medir a proporção de mensagens corretas.
- Testar desalinhamento, diferentes distâncias, luz ambiente e tubo.
- Fotografar a montagem final e registrar condições/medidas.
