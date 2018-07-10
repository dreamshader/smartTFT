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

 - 1 x Arduino Pro Mini 1 x 1.8" TFT with SD-slot
 -  2 x Levelshifter with 4 channels 
 - 1 x Stepup/Stepdown Regulator 5 <-> 3V3 
 - 1 x LDR  
 - 1 x Buzzer 
 - 1 x Resistor 10 kOhm 
 - 2 x Resistor 4.7 kOhm
 - 1 x Resistor 100 Ohm 
 - 2 x Ceramic Capacitor 100 nF 
 - 1 x Proto-PCB 16 rows/32 columns (around 42 x 83 mm) 
 - 1 x Proto-PCB 16 rows/6 columns (around 42 x 15 mm)  
 - 1 x Stereo Jack female 3.5 mm 
 - 1 x DC Jack female 3.5 mm x 1.35 mm 
 - 1 x 4x1 Pin Header 
 - a bunch of colored wires 0.14 mm

**TODO**


**Wiring**

| Arduino | 1.8" TFT |
|--|--|
| Pin #10 |TFT_CS |
| Pin #9 |TFT_RST |
| Pin #8 |TFT_DC |
| Pin #13 |TFT_SCL |
| Pin #11 |TFT_SDA |
| Pin #7 |SD_CS |
| Pin #12 |SD_MISO |
| Pin #11 |SD_MOSI|
| Pin #13 |SD_SCL |

Alle o.g. Verbindungen gehen vom **Arduino** aus auf die **HV-Seite (5V)** des/der Levelshifter und von der **LV-Seite (3V3)** zum **TFT**.

**Achtet zudem darauf, dass der Jumper (Lötbrücke) J1 des TFT offen ist.**

  

**Pin #6** des Arduino geht **direkt** auf den Anschluss LED+ des Displays. Diese Verbindung dient zum Dimmen der Hintergrund-Beleuchtung.  

Am Arduino wird ausserdem am Pin A0 der LDR angeschlossen. Der 10 kOhm Widerstand geht von A0 als pulldown nach GND. Der zweite Anschluss des LDR geht auf Vcc (5V). Der LDR soll es ermöglichen das Dimmen des Displays von der Umgebungs-Helligkeit abhängig zu machen.

**Folgende Funktionen sind im aktuellen Prototypen umgesetzt:**

-   print()
-   drawLine()
-   drawFastHLine()
-   drawFastVLine()
-   drawRect()
-   fillRect()
-   drawCircle()
-   fillCircle()
-   drawTriangle()
-   fillTriangle()
-   drawRoundRect()
-   fillRoundRect()
-   setRotation()
-   setTextWrap()
-   fillScreen()
-   invertDisplay()
-   drawCircleHelper()
-   fillCircleHelper()
-   drawChar()
-   setCursor()
-   setTextSize()

und, weil die Beleuchtung über einen PWM-föhigen Ausgang des Arduino angesteuert wird

-   setbrightness()
