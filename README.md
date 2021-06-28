# Controlador de motor Arduino
Control para motor mediante API Rest usando placa ESP8266 y motor ULN2003.

## Circuito
Fuente del circuito: https://www.geekering.com/categories/embedded-sytems/esp8266/ricardocarreira/esp8266-nodemcu-controling-stepper-motor-with-uln2003-driver/
![alt text](https://i.imgur.com/T4ufqL4.png)

## Ejecutar
1. Monta el circuito
2. Crea el archivo WifiCredentials.ino como el ejemplo con las credenciales de tu Wifi
3. Flashea a ESP8266 con Arduino IDE (https://www.arduino.cc/en/software)

## Uso
Para usarlo crea una petición POST a la IP de la placa (se recomienda configurar IP estática desde el router) con los parámetros steps (pasos) y reverse (dirección) 0 ó 1.
application/x-www-form-urlencoded

** MIT License **
