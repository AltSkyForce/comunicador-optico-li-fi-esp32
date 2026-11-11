# Progresso e próximos passos

**Data:** 10/11/2026  
**Apresentação prevista:** 18/11/2026

## Confirmado em bancada
- Arduino IDE configurado e ESP32 programado por USB.
- LED de alto brilho piscando com GPIO23.
- LDR medido pelo GPIO34 (ADC de 12 bits).
- Comunicação óptica LED → LDR com tubo de papelão.
- Sequência de bits `10110` recuperada a partir de leituras do LDR.

## Ainda não validado
- Reconstrução de palavras e mensagens completas.
- Sincronismo independente (usa-se apenas um ESP32).
- Uso do buzzer passivo e especificações de ligação.
- Ensaio da apresentação e relatório final.

## Planejamento para o buzzer
Um buzzer passivo está disponível, mas **ainda não foi conectado**. É necessário
verificar se é piezoelétrico ou eletromagnético e suas especificações.
Um alto-falante ou buzzer de corrente elevada não deve ser ligado diretamente ao GPIO.
O som será um recurso de feedback, não o canal de recepção dos dados.

## Próxima sessão
1. Revisar as conexões (alimentação USB desligada durante ajustes).
2. Validar o código de envio/recepção de bytes como protótipo.
3. Fazer a primeira mensagem aparecer reconstruída no Monitor Serial.
4. Adicionar registros e fotos ao GitHub.
