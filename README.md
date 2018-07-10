# smartTFT
**Brief**


**Goal**
There is a lot of small and cheap color TFT displays around and with this project I want to give some of them the possibility to remotely control its content. Control is done by most common function calls of the Arduino GFX Library that are transferred to a µController that executes them.

**First Prototype**  
First prototype is a 1.8" TFT with a ST7735 controller and additional SD-card slot. 
As a µController an Arduino Pro Mini is used.
Communication is done using the UART of the Arduino.
A self-made case will hold the components.
A buzzer is used to realize an alarm-function, a LDR makes ist possible to change brightness of the display depending on ambient light.

***Be aware ... this is a work-in-progress project. Some parts may not or not proper work. Use at your own risc!***

**Parts List 1st Prototype**

1 x Arduino Pro Mini
1 x 1.8" TFT mit Kartenslot ( 16-polige Anschlussleiste so wie -> [das hier](https://www.ebay.de/itm/1-8-inch-ST7735R-SPI-128-160-TFT-LCD-Display-Module-with-PCB-for-Arduino-51/380809480973) <- )  
2 x Levelshifter mit 4 Kanälen ( ich verwende -> [solche hier](https://www.ebay.de/itm/I2C-Pegelwandler-Level-Shifter-Konverter-3-3V-5V-bidirektional-4-Kanal-Arduino/171979768309) <- )  
1 x Spannungsregler 5 <-> 3V3 ( da nehme ich derzeit -> [solche hier](https://www.ebay.de/itm/DC-DC-Step-Down-Step-Up-Converter-1-8V-5V-to-3-3V-Wifi-Bluetooth-ESP8266-CC1101/263351138950) <- )  
1 x LDR ( -> [solche](https://www.ebay.de/itm/10-Stuck-LDR-Foto-Widerstand-GL5516-Photoresistor-ideal-fur-Arduino/123121697182) <- sind recht preiswert zu bekommen )  
1 x Buzzer
1 x Widerstand 10 kOhm
1 x Widerstand 100 Ohm
2 x KerKo 100 nF als Abblock-Kondensatoren
1 x Streifenraster-Platine RM 2.54 mm, 16 Reihen und 32 Spalten (ca. 42 x 83 mm)  
1 x Streifenraster-Platine RM 2.54 mm, 6 Reihen und 32 Spalten (ca. 42 x 15 mm)
Stereo Klinkenbuchse 3.5
DC Buchse 
4x1 Pin Header 2.54
ein paar farbige Kabel, 0.14 Querschnitt



**TODO**

