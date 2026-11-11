# Comunicador Óptico de Dados — Li-Fi de Baixo Custo

> Projeto didático em desenvolvimento: transmissão de texto por luz visível com **um ESP32, um LED e um fotorresistor (LDR)**.

**Estado:** ✅ LED, LDR e transmissão óptica de bits validados em bancada; transmissão de texto ainda pendente.  
**Apresentação prevista:** 18/11/2026.

## Objetivo

Enviar uma mensagem de texto por pulsos luminosos: o ESP32 transforma cada byte em bits, controla um LED, mede a luz recebida pelo LDR e reconstrói os bytes a partir das leituras do sensor. É uma demonstração educacional de comunicação óptica de baixa velocidade, inspirada no conceito de Li-Fi; **não é uma implementação de rede Li-Fi padronizada**.

## Arquitetura atual: um ESP32

```mermaid
flowchart TD
    PC[Computador / Monitor Serial] -->|Mensagem por USB| ESP[ESP32]
    ESP -->|GPIO 23| LED[LED + resistor]
    LED -->|Pulsos de luz no ar| LDR[LDR + divisor de tensão]
    LDR -->|Leitura analógica GPIO 34| ESP
    ESP -->|Texto reconstruído por USB| PC
```

**Importante:** transmissor e receptor compartilham o mesmo ESP32, que conhece os instantes de envio. É um **laço óptico local (loopback)**, não uma comunicação entre dois dispositivos independentes. O programa **não copia** a mensagem original para a saída recebida: ele reconstrói o texto a partir das medições no LDR. Uma versão futura pode usar dois microcontroladores para transmitir sem sincronização interna.

## Componentes

- 1 ESP32 DevKit de 38 pinos (placa preta fotografada; conferir pinagem na própria placa)
- 1 LED visível, preferencialmente de alto brilho
- 1 LDR (fotorresistor)
- 1 resistor de **220 Ω ou 330 Ω** para o LED
- 1 resistor de **10 kΩ** para o divisor do LDR
- 1 ou 2 protoboards, fios jumper, cabo USB de **dados** e notebook
- Tubo de papelão utilizado e validado para reduzir a luz ambiente

**Atenção:** os valores dos resistores fotografados ainda precisam ser confirmados pelas faixas/multímetro. Um módulo conversor USB-serial vermelho que aparece nas fotos **não é outro ESP32** e não é necessário nesta montagem.

## Como começar

1. Instale [Arduino IDE](https://www.arduino.cc/en/software) e adicione o pacote **esp32 by Espressif Systems**.
2. Escolha a placa **ESP32 Dev Module** (ponto de partida) e a porta correspondente ao ESP32.
3. Veja [hardware/ligacoes.md](hardware/ligacoes.md) antes de energizar o circuito.
4. Teste `firmware/01_teste_led/01_teste_led.ino`.
5. Teste `firmware/02_teste_ldr/02_teste_ldr.ino`.
6. Execute `firmware/03_comunicador_optico/03_comunicador_optico.ino` e envie uma frase pelo Monitor Serial.
7. Anote resultados e ajustes em [testes/registro-de-testes.md](testes/registro-de-testes.md).

> Os testes de LED, LDR e bits foram executados em bancada em 10/11/2026. O código de comunicação de texto incluído é uma proposta inicial **ainda não validada no hardware**.

## Organização dos arquivos

```text
comunicador-optico-li-fi-esp32/
├── README.md
├── .gitignore
├── firmware/
│   ├── 01_teste_led/
│   ├── 02_teste_ldr/
│   └── 03_comunicador_optico/
├── hardware/
│   ├── componentes.md
│   └── ligacoes.md
├── docs/
│   ├── fundamentos.md
│   ├── instalacao-arduino-ide.md
│   └── roteiro-apresentacao.md
├── testes/
│   └── registro-de-testes.md
├── imagens/
│   └── README.md
└── apresentacao/
    └── README.md
```

## Como funciona a codificação

Cada caractere é transmitido como oito bits. Por exemplo, `A` em ASCII equivale a `01000001`. LED aceso representa 1; LED apagado, 0. O código integrado faz uma calibração e lê o LDR durante cada intervalo de bit. Começamos com intervalos longos porque o LDR é lento em comparação com sensores ópticos próprios para dados.

## Resultados

**Resultados parciais medidos em 10/11/2026:** LED ligado ~3270 e desligado ~1900 sem tubo; com tubo, ligado tipicamente ~2850–2915 e desligado 0. A sequência binária `10110` foi recebida corretamente em várias repetições. Veja [registro de testes](testes/registro-de-testes.md). **A transmissão de frases completas ainda não foi comprovada.**

## Próximas melhorias

- Manter o isolamento com tubo de papelão e documentar fotos.
- Medir a taxa de erros e ajustar duração dos bits.
- Avaliar buzzer passivo como feedback sonoro após identificar suas especificações elétricas.
- Implementar sincronização independente e um segundo microcontrolador (opcional).

## Autoria e licença

Preencher nome(s), escola/curso e orientador antes de publicar. **Nenhuma licença foi escolhida neste pacote**; consulte `docs/licenca-e-creditos.md`.
