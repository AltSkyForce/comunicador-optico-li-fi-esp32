# Fundamentos e protocolo da demonstração

## O que significa transmitir dados pela luz?

Um sinal elétrico digital controla o LED, alternando sua luminosidade. A luz atravessa o ar e incide no LDR, cuja resistência varia com a iluminação. Um divisor resistivo converte essa variação em tensão para o ADC do ESP32.

## É código Morse?

É uma analogia útil, mas o esquema usado aqui **não é o código Morse**. Em vez de pontos e traços, transmitimos **bits binários** com duração fixa: `1 = LED aceso`, `0 = LED apagado`.

## Codificação usada no protótipo

- Cada byte de entrada contém oito bits, transmitidos do mais significativo ao menos significativo (MSB primeiro).
- Exemplo: `A` → ASCII decimal 65 → `01000001`.
- Cada bit ocupa, inicialmente, **180 ms**; a leitura do LDR ocorre após **130 ms**, para permitir estabilização.
- O receptor classifica a tensão medida de acordo com um limiar calibrado entre LED apagado e LED aceso.
- A demonstração usa o **mesmo ESP32** para acionar o LED e fazer a leitura do sensor no instante combinado.
- Não existe, nesta versão, preâmbulo, detecção independente de início, correção de erros ou clock de recepção separado.

## Calibração e condições

O programa integrado mede o LDR com o LED apagado e aceso, encontra um limiar médio e verifica se a diferença entre as duas leituras é suficiente. Caso o contraste seja pequeno, pede para aproximar e alinhar o LED ou reduzir a luz ambiente.

## Velocidade e limites

O LDR é barato, mas reage relativamente devagar. O valor de 180 ms por bit resulta em aproximadamente 5,6 bits por segundo, antes de pausas e processamento (aprox. 0,7 byte/s apenas durante os bits). O circuito não é indicado para internet de alta velocidade nem comunicação a longa distância.

## Como explicar o resultado corretamente

O Monitor Serial mostra a mensagem digitada e os bytes reconstruídos **pela leitura óptica**. Essa verificação comprova o percurso LED → luz → LDR no protótipo, mas não comprova a existência de um receptor independente.
