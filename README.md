# smartTFT



Brief description
--
There is a lot of small and cheap color TFT displays around and with this project I want to give some of them the possibility to remotely control its content. Control is done by most common function calls of the Arduino GFX Library that are transferred to a µController that executes them.

First Prototype
--  
First prototype is a 1.8" TFT with a ST7735 controller and additional SD-card slot. 
As a µController an Arduino Pro Mini is used.
Communication is done using the UART of the Arduino.
A self-made case will hold the components.
A buzzer is used to realize an alarm-function, a LDR makes ist possible to change brightness of the display depending on ambient light.

***Be aware ... this is a work-in-progress project. Some parts may not or not proper work. Use at your own risc!***

Parts List 1st Prototype
--
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
 - 1 x DC Jack female 3.5 mm x 1.1 mm 
 - 1 x 4x1 Pin Header 
 - a bunch of colored wires 0.14 mm

Wiring via Levelshifter
--
| Arduino | Levelshifter| Levelshifter|1.8" TFT |
|--|--|--|--|
| Pin #10 |HV*| LV** | TFT_CS |
| Pin #9 |HV| LV|TFT_RST |
| Pin #8 |HV| LV|TFT_DC |
| Pin #13 |HV| LV|TFT_SCL |
| Pin #11 |HV| LV|TFT_SDA |
| Pin #7 |HV| LV|SD_CS |
| Pin #12 |HV| LV|SD_MISO |
| Pin #11 |HV| LV|SD_MOSI|
| Pin #13 |HV| LV|SD_SCL |

*HV means High Voltage Side
**LV means Low Voltage Side

---

Because Vcc of the TFT is 5V **be aware** that **Jumper J1** on the back side of TFT is **open!** Otherwise the display is damaged.

Direct Wiring
--  
|Arduino|Target 1  | Target 2| is for |
|--|--|--|--|
|Pin #5  | 100 Ohm | buzzer | limit current |
|Pin #6  | TFT LED+ | -- |dim backlight |
|Pin A0  | LDR |-- | light sense |
|Pin A0  | 10 kOhm |GND | pulldown|



Realized GFX-functions
--
 - drawLine() 
 - drawFastHLine() 
 - drawFastVLine() 
 - drawRect() 
 - fillRect()
 - drawCircle() 
 - fillCircle() 
 - drawTriangle() 
 - fillTriangle()
 - drawRoundRect() 
 - fillRoundRect() 
 - setRotation() 
 - setTextWrap()
 - fillScreen() 
 - setTextColor() 
 - fillScreen() 
 - invertDisplay()
 - drawCircleHelper() 
 - fillCircleHelper() 
 - drawBitmap() 
 - drawChar()
 - setCursor() 
 - setTextSize() 
 - height() 
 - width() 
 - write() 
 - drawPixel()
 - print() 
 - println()

and. last but not least,
-   setbrightness()

for dimming the backlight.


