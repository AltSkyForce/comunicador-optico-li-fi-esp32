# Preparação do Arduino IDE (Windows)

1. Baixe o programa pelo site oficial: <https://www.arduino.cc/en/software>.
2. Instale e abra o **Arduino IDE 2**.
3. Em **File → Preferences**, no campo **Additional Boards Manager URLs**, insira:

   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`

4. Abra **Boards Manager**, pesquise `esp32` e instale **esp32 by Espressif Systems**.
5. Conecte a placa preta ESP32 por um cabo USB **de dados**.
6. Em **Select Other Board and Port**, escolha inicialmente **ESP32 Dev Module** e a porta COM correspondente. Se a porta não aparecer, verifique cabo e driver USB da placa.
7. Abra um programa `.ino`; clique **Verify** para compilar e **Upload** para enviar à placa.
8. Abra **Serial Monitor** e selecione a velocidade **115200 baud**.

**Importante:** o nome de porta (COM5, COM6, etc.) pode mudar. A opção certa é a porta que aparece/desaparece quando você conecta/desconecta o ESP32.

**Segurança:** faça as ligações sempre com USB desconectado; nunca aplique 5 V diretamente nos GPIO.
