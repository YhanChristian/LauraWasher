# LauraWasher - Computador para Máquina de Lavar
Washer Machine computer firmware (based on ATmega8-16pu microcontroller)

Primeiros testes do hardware https://youtu.be/XmeAUAEXgaU

Primeira lavagem oficial https://youtu.be/Mpq0ZS1fTXU

![alt tag](https://igcdn-photos-f-a.akamaihd.net/hphotos-ak-xaf1/t51.2885-15/11184517_1581104945490485_549273488_n.jpg)

Requisitos técnicos:
* Motor principal com reversão
* Solenóide de inundação
* Bomba de água para exaustão
* Pressostato variável para níveis de água
* Sensor da tampa


Features:
* 7 modos de operação (implementados o modo 2 - Lavagem Pesada e 3 - Lavagem Normal até o momento).
* Porta serial para monitoração/controle da máquina.


Próximas features:
* Implementação de todos modos, incluindo enxague e centrifugação separados.
* Porta LAN para acesso a internet (monitoração via mobile app)
* Sensor de temperatura do motor
* Controle dos motores via PWM para reduzir o aquecimento, atrito de engrenagens, melhorar o torque na carambola e reduzir o consumo de energia elétrica.


