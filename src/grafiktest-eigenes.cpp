// #include <stdio.h>
// #include <stdlib.h>
// #include <strings.h>
// #include <stdarg.h>

#include <iostream>
#include <string>

#include "smartTFT.h"








// tft_fillScreen(ST7735_BLACK);
// tft_drawPixel(tft_width()/2, tft_height()/2, ST7735_GREEN);
// tft_invertDisplay(true);
// tft_invertDisplay(false);
// tft_drawLine(0, 0, x, tft_height()-1, color);
// tft_setCursor(0, 0);
// tft_setTextColor(color);
// tft_setTextWrap(true);
// tft_print(text);
// tft_drawFastHLine(0, y, tft_width(), color1);
// tft_drawFastVLine(x, 0, tft_height(), color2);
// tft_drawRect(tft_width()/2 -x/2, tft_height()/2 -x/2 , x, x, color);
// tft_fillRect(tft_width()/2 -x/2, tft_height()/2 -x/2 , x, x, color1);
// tft_fillCircle(x, y, radius, color);
// tft_drawCircle(x, y, radius, color);
// tft_drawTriangle(w, y, y, x, z, x, color);
// tft_drawRoundRect(x, y, w, h, 5, color);
// tft_setTextSize(1);
// tft_println("Hello World!");
// tft_print(8675309, HEX); // print 8,675,309 out in HEX!
// tft_fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
// tft_fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
// 

int main( int argc, char *argv[] )
{
    int retVal = 0;

    smartTFT *display = new smartTFT();
    display->tft_println("lalala");
    display->tft_println(25);
    display->tft_println(25,HEX);
    display->tft_println();

    display->tft_print("lalala");
    display->tft_print(25);
    display->tft_print(25,HEX);

    delete display;

    return( retVal );
}

