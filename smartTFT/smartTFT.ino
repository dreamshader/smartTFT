/***************************************************
 smartTFT ...

    Copyright (C) 2018 Dreamshader (aka Dirk Schanz)

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

Der Sketch verwendet 27212 Bytes (88%) des Programmspeicherplatzes. Das Maximum sind 30720 Bytes.
Globale Variablen verwenden 1334 Bytes (65%) des dynamischen Speichers, 714 Bytes für lokale Variablen verbleiben. Das Maximum sind 2048 Bytes.



 ****************************************************/

// config

#define _SUPPORT_IIC_
#define _SUPPORT_SDCARD_
#define _SUPPORT_LDR_



// 


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#ifdef _SUPPORT_IIC_
#include <Wire.h>
#endif // _SUPPORT_IIC_

#ifdef _SUPPORT_SDCARD_
#include <SD.h>
#endif // _SUPPORT_SDCARD_


//
#define PIN_BUZZER           5
#define TFT_BACKLIGHT        6
#define LDR_INPUT           A1
//
#define TFT_CS              10
#define TFT_RST              9
#define TFT_DC               8
#define TFT_SCLK            13
#define TFT_MOSI            11
#define SD_CS                7
#define SD_MISO             12
#define SD_MOSI       TFT_MOSI
#define SD_SCLK       TFT_SCLK
//
#define SERIAL_BAUD      38400
#define I2C_ADDRESS         12
#define SD_CHECK_INTVAL  10000
#define LDR_CHECK_INTVAL  2000

//


#define BACKLIGHT_FULL     255
#define BACKLIGHT_OFF        0
#define DEFAULT_BACKLIGHT    BACKLIGHT_FULL

#define DEFAULT_FG_COLOR     ST7735_BLACK
#define DEFAULT_BG_COLOR     ST7735_WHITE

//
// some globals needed 
//
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
bool cardPresent = false;
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
uint16_t tftBackgroundColor;
uint16_t tftForegroundColor;
//
// SD related
//
#ifdef _SUPPORT_SDCARD_
Sd2Card  tftSDCard;
SdVolume tftVolume;
SdFile   tftRootFile;
File     tftFile;
#endif // _SUPPORT_SDCARD_
//
//

#ifdef _SUPPORT_IIC_
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() 
{
    Wire.write("hello "); // respond with message of 6 bytes
                          // as expected by master
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) 
{
    while (1 < Wire.available()) 
    { // loop through all but the last
        char c = Wire.read(); // receive byte as a character
        Serial.print(c);         // print the character
    }

    int x = Wire.read();    // receive byte as an integer
    Serial.println(x);         // print the integer
}
#endif // _SUPPORT_IIC_

//
// ------------------------------
//
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
#ifdef NEVERDEF
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
//    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') 
    {
        stringComplete = true;
    }
    else
    {
      inputString += inChar;
    }
  }
}
#endif

#define CMD_INVAL             -1
#define CMD_NONE               0
#define CMD_SET_BG             1	
#define CMD_SET_FG             2
#define CMD_BRIGHTNESS         3
#define CMD_PRINTTEXT          4
#define CMD_TEXTWRAP           5
#define CMD_SETROTATION        6
#define CMD_CLEAR              7
#define CMD_DRAWTEXT           8
#define CMD_DRAWLINE           9
#define CMD_FAST_H_LINE       10
#define CMD_FAST_V_LINE       11
#define CMD_DRAWRECT          12
#define CMD_FILLRECT          13
#define CMD_DRAWCIRCLE        14
#define CMD_FILLCIRCLE        15
#define CMD_DRAWTRIANGLE      16
#define CMD_FILLTRIANGLE      17
#define CMD_DRAWROUNDRECT     18
#define CMD_FILLROUNDRECT     19
#define CMD_FILLSCREEN        20
#define CMD_INVERTDISPLAY     21
#define CMD_DRAWCIRCLEHELPER  22
#define CMD_FILLCIRCLEHELPER  23
#define CMD_DRAWBITMAP        24
#define CMD_DRAWCHAR          25
#define CMD_SETCURSOR         26
#define CMD_SETTEXTSIZE       27

#define CMD_TFT_HEIGHT        28
#define CMD_TFT_WIDTH         29
#define CMD_DRAWPIXEL         30
#define CMD_TFT_WRITE         31
#define CMD_TFT_PRINT         32
#define CMD_TFT_PRINTLN       33
#define CMD_SETTEXTCOLOR      34



#define MAX_ARGS            7

// Color definitions
//#define  ST7735_BLACK   0x0000
//#define ST7735_BLUE    0x001F
//#define ST7735_RED     0xF800
//#define ST7735_GREEN   0x07E0
//#define ST7735_CYAN    0x07FF
//#define ST7735_MAGENTA 0xF81F
//#define ST7735_YELLOW  0xFFE0
//#define ST7735_WHITE   0xFFFF



#ifdef _SUPPORT_SDCARD_

int sdInit()
{
    int retVal;

    return(retVal);
}

int sdCardType( void )
{
    int retVal;

    return(retVal);
}

int sdVolumeInfo( void )
{
    int retVal;

    return(retVal);
}

char *sdListRoot( void )
{
    char *pLine;

    return(pLine);
}

int sdCWD( char *dirname )
{
    int retVal;

    return(retVal);
}

char *sdListFiles( void )
{
    char *pLine;

    return(pLine);
}

int sdOpenFile( char* pFileName )
{
    int retVal;

    return(retVal);
}

int sdCloseFile( void )
{
    int retVal;

    return(retVal);
}

uint8_t sdReadChar( void )
{
    uint8_t retVal;

    return(retVal);
}

uint16_t sdReadInt16( void )
{
    uint16_t retVal;

    return(retVal);
}

uint32_t sdReadInt32( void )
{
    uint32_t retVal;

    return(retVal);
}

int sdReadBuffer( char* pBuffer, int maxLen )
{
    int retVal;

    return(retVal);
}

char *sdReadLine( void )
{
    char *pLine;

    return(pLine);
}


#endif // _SUPPORT_SDCARD_



void tftPrintText( int xPos, int yPos, uint16_t color, int textSize, bool wrap, char* pText )
{
  tft.setTextWrap(wrap);
  tft.setCursor(xPos, yPos);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  if( pText != NULL )
  {
  tft.print(pText);
  }
  else
  {
  tft.print("NULL!!");
  }
}

void tftDrawText( int xPos, int yPos, int color, int textSize, char* pText )
{
    tftPrintText( xPos, yPos, color, textSize, true, pText );
}

void tftDrawLine(int startX, int startY, int endX, int endY, uint16_t color)
{
    tft.drawLine(startX, startY, endX, endY, color);
}

void tftDrawFastHLine(int xPos, int yPos, int len, uint16_t color)
{
    tft.drawFastHLine(xPos, yPos, len, color);
}

void tftDrawFastVLine(int xPos, int yPos, int len, uint16_t color)
{
    tft.drawFastVLine(xPos, yPos, len, color);
}

void tftDrawRect(int startX, int startY, int width, int height, uint16_t color)
{
    tft.drawRect(startX, startY, width, height, color);
}

void tftFillRect(int startX, int startY, int width, int height, uint16_t color)
{
    tft.fillRect(startX, startY, width, height, color);
}

void tftDrawCircle(int xPos, int yPos, int radius, uint16_t color)
{
    tft.drawCircle(xPos, yPos, radius, color);
}

void tftFillCircle(int xPos, int yPos, int radius, uint16_t color)
{
    tft.fillCircle(xPos, yPos, radius, color);
}

void tftDrawTriangle(int topX, int topY, int leftBottomX, int leftBottomY, 
                      int rightBottomX, int rightBottomY, uint16_t color)
{
    tft.drawTriangle(topX, topY, leftBottomX, leftBottomY, 
                     rightBottomX, rightBottomY, color);
}

void tftFillTriangle(int topX, int topY, int leftBottomX, int leftBottomY, 
                      int rightBottomX, int rightBottomY, uint16_t color)
{
    tft.fillTriangle(topX, topY, leftBottomX, leftBottomY, 
                     rightBottomX, rightBottomY, color);
}

void tftDrawRoundRect(int startX, int startY, int width, int height, int radius, uint16_t color)
{
    tft.drawRoundRect(startX, startY, width, height, radius, color);
}

void tftFillRoundRect(int startX, int startY, int width, int height, int radius, uint16_t color)
{
    tft.fillRoundRect(startX, startY, width, height, radius, color);
}

void tftSetRotation( int rotation )
{
    tft.setRotation( rotation );
}


void tftSetTextWrap( bool wrap )
{
    tft.setTextWrap(wrap);
}

void tftClear( void )
{
    tft.fillScreen(tftBackgroundColor);
}

void tftSetBackground( uint16_t color )
{
    tftBackgroundColor = color;
}


void tftSetForeground( uint16_t color )
{
    tftForegroundColor = color;
}


void SetTextColor1Arg(uint16_t fgColor)
{
    tft.setTextColor(fgColor);
}

void SetTextColor2Args(uint16_t fgColor, uint16_t bgColor)
{
    tft.setTextColor(fgColor, bgColor);

}


void tftSetBrightness( int value )
{
    analogWrite(TFT_BACKLIGHT, value);
}


void tftFillScreen( uint16_t color )
{
    tft.fillScreen( color );
}

void tftInvertDisplay( boolean invert )
{
    tft.invertDisplay( invert );
}

void tftDrawCircleHelper( int16_t xPos, int16_t yPos, int16_t radius, int8_t cornername, uint16_t color )
{
    tft.drawCircleHelper( xPos, yPos, radius, cornername, color );
}

void tftFillCircleHelper( int16_t xPos, int16_t yPos, int16_t radius, int8_t cornername, int16_t delta, uint16_t color )
{
    tft.fillCircleHelper( xPos, yPos, radius, cornername, delta, color );
}

void tftDrawBitmap( int16_t xPos, int16_t yPos, const uint8_t *bitmap, int16_t width, int16_t height, uint16_t color )
{
    tft.drawBitmap( xPos, yPos, bitmap, width, height, color );
}

void tftDrawChar( int16_t xPos, int16_t yPos, unsigned char character, uint16_t color, uint16_t background, uint8_t size )
{
    tft.drawChar( xPos, yPos, character, color, background, size );
}

void tftSetCursor( int16_t xPos, int16_t yPos )
{
    tft.setCursor( xPos, yPos );
}

void tftSetTextSize( uint8_t size )
{
    tft.setTextSize( size );
}

int tftHeight( void )
{
    return( tft.height() );
}

int tftWidth( void )
{
    return( tft.width() );
}

// virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
size_t tftWrite( uint8_t char2Write )
{
    return( tft.write( char2Write ) );
}

  // This MUST be defined by the subclass:
int tftDrawPixel(int xPos, int yPos, uint16_t color)
{
    tft.drawPixel( xPos, yPos, color );
    return(0);
}


//    size_t tft_print(string data);
//    size_t tft_print(const char data[]);
//    size_t tft_print(char data);
//    size_t tft_print(unsigned char data, int fmt = DEC);
//    size_t tft_print(int data, int fmt = DEC);
//    size_t tft_print(unsigned int data, int fmt = DEC);
//    size_t tft_print(long data, int fmt = DEC);
//    size_t tft_print(unsigned long data, int fmt = DEC);
//    size_t tft_print(double data, int fmt = 2);
//    size_t tft_println(void);
int tftPrint_Text( int printCmd, char *pText )
{
    int retVal = 0;
    
    switch( printCmd )
    {
        case CMD_TFT_PRINT:
            tft.print( pText );
            break;
        case CMD_TFT_PRINTLN:
            tft.println( pText );
            break;
    }

    return( retVal );
}

int tftPrint_Long( int printCmd, long argLong )
{
    int retVal = 0;
    
    switch( printCmd )
    {
        case CMD_TFT_PRINT:
            tft.print( argLong );
            break;
        case CMD_TFT_PRINTLN:
            tft.println( argLong );
            break;
    }

    return( retVal );
}

int tftPrint_LongFmt( int printCmd, long argLong, int format )
{
    int retVal = 0;
    
    switch( printCmd )
    {
        case CMD_TFT_PRINT:
            tft.print( argLong, format );
            break;
        case CMD_TFT_PRINTLN:
            tft.println( argLong, format );
            break;
    }

    return( retVal );
}

int tftPrint_Double( int printCmd, double argDouble )
{
    int retVal = 0;
    
    switch( printCmd )
    {
        case CMD_TFT_PRINT:
            tft.print( argDouble );
            break;
        case CMD_TFT_PRINTLN:
            tft.println( argDouble );
            break;
    }

    return( retVal );
}

int tftPrint_DoubleFmt( int printCmd, double argDouble, int format )
{
    int retVal = 0;
    
    switch( printCmd )
    {
        case CMD_TFT_PRINT:
            tft.print( argDouble, format );
            break;
        case CMD_TFT_PRINTLN:
            tft.println( argDouble, format );
            break;
    }

    return( retVal );
}


//
int getInteger( char* pCommand )
{
    int retVal = CMD_INVAL;

    if( pCommand != NULL )
    {
        int i;
        for(i = 0; pCommand[i] != '\0' && !isDigit(pCommand[i]) ; i++ )
            ;

        if( isDigit(pCommand[i]) )
        {
            retVal = atoi(&pCommand[i]);
        }
    }

    return( retVal );
}


uint8_t getUint8( char* pCommand )
{
    uint8_t retVal = CMD_INVAL;

    if( pCommand != NULL )
    {
        int i;
        for(i = 0; pCommand[i] != '\0' && !isDigit(pCommand[i]) ; i++ )
            ;

        if( isDigit(pCommand[i]) )
        {
            retVal = (uint8_t) atoi(&pCommand[i]);
        }
    }

    return( retVal );
}

unsigned char getUChar( char* pCommand )
{
    return( (unsigned char) getUint8( pCommand ) );
}

//

long getLong( char* pCommand )
{
    long retVal = CMD_INVAL;

    if( pCommand != NULL )
    {
        int i;
        for(i = 0; pCommand[i] != '\0' && !isDigit(pCommand[i]) ; i++ )
            ;

        if( isDigit(pCommand[i]) )
        {
            retVal = atol(&pCommand[i]);
        }
    }

    return( retVal );
}


double getDouble( char* pCommand )
{
    double retVal = CMD_INVAL;

    if( pCommand != NULL )
    {
        int i;
        for(i = 0; pCommand[i] != '\0' && !isDigit(pCommand[i]) ; i++ )
            ;

        if( isDigit(pCommand[i]) )
        {
            retVal = atof(&pCommand[i]);
        }
    }

    return( retVal );
}



bool getBoolean( char* pCommand )
{
    bool retVal;

    if( pCommand != NULL )
    {
        int intVal;
        if( (intVal = getInteger( pCommand )) > 0 )
        {
            retVal = true;
        }
        else
        {
            retVal = false;
        }
    }

    return( retVal );
}

//

char *getText( char *pData, int *pLength )
{
    char *retVal = NULL;
    static String resultString = "";

    *pLength = 0;

    if( pData != NULL )
    {
        int txtLength, endText;

        if( pData[0] == '"' )
        {
            pData++;
            for( txtLength = endText = 0; 
                 pData[txtLength] != '\0' && endText == 0; txtLength++ )
            {
                if( pData[txtLength] == '"' )
                {
                    if( txtLength > 0 )
                    {
                        if( pData[txtLength] != '\\' )
                        {
                            endText = 1;
                        }
                    }
                    else
                    {
                        endText = 1;
                    }
                }
                else
                {
                    resultString += pData[txtLength];
                }
            }
            resultString += '\0';
            retVal = resultString.c_str();
        }
        else
        {
            retVal = (char*) "NO TEXT";
        }
    }

    return( retVal );
}

char *getBitmap( char *pData, int *pLength )
{
    char *retVal = NULL;

    *pLength = 0;

    if( pData != NULL )
    {
    }

    return( retVal );
}





int getNextArgPos( char* pCommand )
{
    int retVal = 0;

    if( pCommand != NULL )
    {
        int i;
        for(i = 0; pCommand[i] != '\0' && pCommand[i] != ',' ; i++ )
            ;

        switch( pCommand[i] )
        {
            case ',':
                retVal = i+1;
                break;
            default:
                retVal = -1;
                break;
        }
    }

    return( retVal );

}

//
int commandParser( String &dataRead )
{
    int retVal = 0;
    int argInt;
    int argBrightness;
    int argXPos;
    int argYPos;
    int argStartX;
    int argStartY;
    int argWidth;
    int argHeight;
    int argRadius;
    int argTopX;
    int argTopY;
    int argLeftBottomX;
    int argLeftBottomY;
    int argRightBottomX;
    int argRightBottomY;
    int argLen;
    int argEndX;
    int argEndY;
    uint16_t argColor;
    int argSize;
    bool argBoolean;
    int argRotation;
    uint8_t argCornerName;
    uint16_t argDelta;
    unsigned char argChar;
    uint16_t argBackground;
    char* argBitmap = NULL;
    char* argText = NULL;
    int firstArgPos;
    int currArgPos;
    int currArgNum;
    int nextArgPos;
    int textLength;
    int bitmapSize;
    uint16_t argFgColor, argBgColor;
    int setTextColorNumArguments;
    uint8_t argWrite;
    int printNumArguments;
    long printLongArg;
    double printDoubleArg;
    int printArgFmt;

    char *pData = dataRead.c_str();

#ifdef SERIAL_DEBUG
Serial.print("parsing: ");
Serial.println( dataRead );
#endif // SERIAL_DEBUG

    if( pData[0] == 'f' || pData[0] == 'F' )
    {
        for(firstArgPos = 0; pData[firstArgPos] != '\0' && 
              !isDigit(pData[firstArgPos]) ; firstArgPos++ )
            ;
           
        if( isDigit(pData[firstArgPos]) )
        {
            retVal = atoi(&pData[firstArgPos]);

            for(; pData[firstArgPos] != '\0' && 
                  pData[firstArgPos] != '('; firstArgPos++)
                 ;

            if( pData[firstArgPos] == '(' )
            {
                firstArgPos++;
            }
            else
            {
                firstArgPos = -1;
            }

            if( (currArgPos = firstArgPos) >= 0 )
            {
                nextArgPos = 0;
                textLength = 0;
                currArgNum = 1;
                setTextColorNumArguments = 0;
                printNumArguments = 0;

                do
                {
                    currArgPos += nextArgPos;

#ifdef SERIAL_DEBUG
                    Serial.print("Arg# is ");
                    Serial.print( currArgNum );
                    Serial.print(", pos is ");
                    Serial.println( currArgPos );
#endif // SERIAL_DEBUG

                    switch( currArgNum )
                    { 
                        case 1:
                            switch( retVal )
                            {
                                case CMD_TFT_PRINT:
                                case CMD_TFT_PRINTLN:
                                    argText = getText( &pData[currArgPos] ,
                                                  &textLength );
                                    if( argText == NULL )
                                    {
                                        printLongArg = getLong(
                                                         &pData[currArgPos] );
                                        printDoubleArg = getDouble( 
                                                          &pData[currArgPos] );
                                        printNumArguments = 1;
                                    }
                                    else
                                    {
                                        printNumArguments = 1;
                                    }
                                    break;
                                case CMD_SET_BG:
                                case CMD_SET_FG:
                                case CMD_FILLSCREEN:
                                    argColor = (uint16_t) getInteger( 
                                                &pData[currArgPos] );
                                    break;
                                case CMD_SETTEXTCOLOR:
                                    argFgColor = (uint16_t) getInteger( 
                                                  &pData[currArgPos] );
                                    setTextColorNumArguments = 1;
                                    break;
                                case CMD_TFT_WRITE:
                                    argWrite = (uint8_t) getInteger( 
                                                  &pData[currArgPos] );
                                    break;
                                case CMD_BRIGHTNESS:
                                    argBrightness = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_SETTEXTSIZE:
                                    argSize = getInteger( &pData[currArgPos] );
                                    break;
                                case CMD_TEXTWRAP:
                                case CMD_INVERTDISPLAY:
                                    argBoolean = getBoolean( &pData[currArgPos] );
                                    break;
                                case CMD_SETROTATION:
                                    argRotation = getInteger( 
                                                    &pData[currArgPos] );
                                    break;
                                case CMD_CLEAR:
                                    break;
                                case CMD_PRINTTEXT:
                                case CMD_DRAWTEXT:
                                case CMD_FAST_H_LINE:
                                case CMD_FAST_V_LINE:
                                case CMD_DRAWCIRCLE:
                                case CMD_FILLCIRCLE:
                                case CMD_DRAWCIRCLEHELPER:
                                case CMD_FILLCIRCLEHELPER:
                                case CMD_DRAWBITMAP:
                                case CMD_DRAWCHAR:
                                case CMD_SETCURSOR:
                                case CMD_DRAWPIXEL:
                                    argXPos = getInteger( &pData[currArgPos] );
                                    break;
                                case CMD_DRAWLINE:
                                case CMD_DRAWRECT:
                                case CMD_FILLRECT:
                                case CMD_DRAWROUNDRECT:
                                case CMD_FILLROUNDRECT:
                                    argStartX = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWTRIANGLE:
                                case CMD_FILLTRIANGLE:
                                    argTopX = getInteger( 
                                                   &pData[currArgPos] );
                                    break;

                            }
                            break;
                       case 2:
                            switch( retVal )
                            {
                                case CMD_TFT_PRINT:
                                case CMD_TFT_PRINTLN:
                                    printArgFmt = getInteger( 
                                                      &pData[currArgPos] );
                                    if( printArgFmt != 0 )
                                    {
                                        printNumArguments = 2;
                                    }
                                    break;
                                case CMD_PRINTTEXT:
                                case CMD_DRAWTEXT:
                                case CMD_FAST_H_LINE:
                                case CMD_FAST_V_LINE:
                                case CMD_DRAWCIRCLE:
                                case CMD_FILLCIRCLE:
                                case CMD_DRAWCIRCLEHELPER:
                                case CMD_FILLCIRCLEHELPER:
                                case CMD_DRAWBITMAP:
                                case CMD_DRAWCHAR:
                                case CMD_SETCURSOR:
                                case CMD_DRAWPIXEL:
                                    argYPos = getInteger( &pData[currArgPos] );
                                    break;
                                case CMD_DRAWLINE:
                                case CMD_DRAWRECT:
                                case CMD_FILLRECT:
                                case CMD_DRAWROUNDRECT:
                                case CMD_FILLROUNDRECT:
                                    argStartY = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWTRIANGLE:
                                case CMD_FILLTRIANGLE:
                                    argTopY = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_SETTEXTCOLOR:
                                    argBgColor = (uint16_t) getInteger( 
                                                  &pData[currArgPos] );
                                    setTextColorNumArguments = 2;
                                    break;

                            }
                            break;
                       case 3:
                            switch( retVal )
                            {
                                case CMD_PRINTTEXT:
                                case CMD_DRAWTEXT:
                                case CMD_DRAWPIXEL:
                                    argColor = (uint16_t) getInteger( 
                                                      &pData[currArgPos] );
                                    break;
                                case CMD_FAST_H_LINE:
                                case CMD_FAST_V_LINE:
                                    argLen = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWCHAR:
                                    argChar = getUChar( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWBITMAP:
                                    argBitmap = getBitmap( 
                                                   &pData[currArgPos],
                                                   &bitmapSize );
                                    break;
                                case CMD_DRAWCIRCLE:
                                case CMD_FILLCIRCLE:
                                case CMD_DRAWCIRCLEHELPER:
                                case CMD_FILLCIRCLEHELPER:
                                    argRadius = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWLINE:
                                    argEndX = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWRECT:
                                case CMD_FILLRECT:
                                case CMD_DRAWROUNDRECT:
                                case CMD_FILLROUNDRECT:
                                    argWidth = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWTRIANGLE:
                                case CMD_FILLTRIANGLE:
                                    argLeftBottomX = getInteger( 
                                                   &pData[currArgPos] );
                                    break;

                            }
                            break;
                       case 4:
                            switch( retVal )
                            {
                                case CMD_PRINTTEXT:
                                case CMD_DRAWTEXT:
                                    argSize = getInteger( 
                                                      &pData[currArgPos] );
                                    break;
                                case CMD_FAST_H_LINE:
                                case CMD_FAST_V_LINE:
                                case CMD_DRAWCIRCLE:
                                case CMD_FILLCIRCLE:
                                case CMD_DRAWCHAR:
                                    argColor = (uint16_t) getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWLINE:
                                    argEndY = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWCIRCLEHELPER:
                                case CMD_FILLCIRCLEHELPER:
                                    argCornerName = getUint8( 
                                                       &pData[currArgPos] );
                                    break;
                                case CMD_DRAWBITMAP:
                                    argWidth = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWRECT:
                                case CMD_FILLRECT:
                                case CMD_DRAWROUNDRECT:
                                case CMD_FILLROUNDRECT:
                                    argHeight = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWTRIANGLE:
                                case CMD_FILLTRIANGLE:
                                    argLeftBottomY = getInteger( 
                                                   &pData[currArgPos] );
                                    break;

                            }
                            break;
                       case 5:
                            switch( retVal )
                            {
                                case CMD_PRINTTEXT:
                                    argBoolean = getBoolean( &pData[currArgPos] );
                                    break;
                                case CMD_DRAWTEXT:
                                    argText = getText( &pData[currArgPos] ,
                                                  &textLength );
                                    break;
                                case CMD_DRAWLINE:
                                case CMD_DRAWRECT:
                                case CMD_FILLRECT:
                                case CMD_DRAWCIRCLEHELPER:
                                    argColor = (uint16_t) getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_FILLCIRCLEHELPER:
                                    argDelta = (uint16_t) getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWBITMAP:
                                    argHeight = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWCHAR:
                                    argBackground = (uint16_t) getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWROUNDRECT:
                                case CMD_FILLROUNDRECT:
                                    argRadius = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWTRIANGLE:
                                case CMD_FILLTRIANGLE:
                                    argRightBottomX = getInteger( 
                                                   &pData[currArgPos] );
                                    break;

                            }
                            break;
                       case 6:
                            switch( retVal )
                            {
                                case CMD_PRINTTEXT:
                                    argText = getText( &pData[currArgPos] ,
                                                  &textLength );
                                    break;
                                case CMD_DRAWROUNDRECT:
                                case CMD_FILLROUNDRECT:
                                case CMD_FILLCIRCLEHELPER:
                                case CMD_DRAWBITMAP:
                                    argColor = (uint16_t) getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWCHAR:
                                    argSize = getInteger( 
                                                   &pData[currArgPos] );
                                    break;
                                case CMD_DRAWTRIANGLE:
                                case CMD_FILLTRIANGLE:
                                    argRightBottomY = getInteger( 
                                                   &pData[currArgPos] );
                                    break;

                            }
                            break;
                       case 7:
                            switch( retVal )
                            {
                                case CMD_DRAWTRIANGLE:
                                case CMD_FILLTRIANGLE:
                                    argColor = (uint16_t) getInteger( 
                                                   &pData[currArgPos] );
                                    break;

                            }
                            break;
                       default:
                           break;
                    }

                    currArgNum++;

                } while( currArgNum <= MAX_ARGS && 
                                 (nextArgPos = getNextArgPos( 
                                     &pData[currArgPos] ) ) > 0 );
            }
            else
            {
                switch (retVal )
                {
                    case CMD_TFT_HEIGHT:
                    case CMD_TFT_WIDTH:
                        break;
                    default:
                        Serial.println( "NO arg!" );
                        retVal = CMD_INVAL;
                }
            }
        }

        switch( retVal )
        {
            case CMD_SET_BG:
                tftSetBackground( argColor );
                break;
            case CMD_SET_FG:
                tftSetForeground( argColor );
                break;
            case CMD_BRIGHTNESS:
                tftSetBrightness( argBrightness );
                break;
            case CMD_TEXTWRAP:
                tftSetTextWrap( argBoolean );
                break;
            case CMD_PRINTTEXT:
                tftPrintText( argXPos, argYPos, argColor, argSize, 
                              argBoolean, argText );
                break;
            case CMD_SETROTATION:
                tftSetRotation( argRotation );
                break;
            case CMD_CLEAR:
                tftClear( );
                break;
            case CMD_DRAWTEXT:
                tftDrawText( argXPos, argYPos, argColor, argSize, argText );
                break;
            case CMD_DRAWLINE:
                tftDrawLine(argStartX, argStartY, argEndX, argEndY, argColor);
                break;
            case CMD_FAST_H_LINE:
                tftDrawFastHLine(argXPos, argYPos, argLen, argColor);
                break;
            case CMD_FAST_V_LINE:
                tftDrawFastVLine(argXPos, argYPos, argLen, argColor);
                break;
            case CMD_DRAWRECT:
                tftDrawRect(argStartX, argStartY, argWidth, 
                            argHeight, argColor);
                break;
            case CMD_FILLRECT:
                tftFillRect(argStartX, argStartY, argWidth, 
                            argHeight, argColor);
                break;
            case CMD_DRAWCIRCLE:
                tftDrawCircle(argXPos, argYPos, argRadius, argColor);
                break;
            case CMD_FILLCIRCLE:
                tftFillCircle(argXPos, argYPos, argRadius, argColor);
                break;
            case CMD_DRAWTRIANGLE:
                tftDrawTriangle(argTopX, argTopY, argLeftBottomX, 
                                argLeftBottomY, argRightBottomX, 
                                argRightBottomY, argColor);
                break;
            case CMD_FILLTRIANGLE:
                tftFillTriangle(argTopX, argTopY, argLeftBottomX, 
                                argLeftBottomY, argRightBottomX, 
                                argRightBottomY, argColor);
                break;
            case CMD_DRAWROUNDRECT:
                tftDrawRoundRect(argStartX, argStartY, argWidth, 
                                 argHeight, argRadius, argColor);
                break;
            case CMD_FILLROUNDRECT:
                tftFillRoundRect(argStartX, argStartY, argWidth, 
                                 argHeight, argRadius, argColor);
                break;
            case CMD_FILLSCREEN:
                tftFillScreen( argColor );
                break;
            case CMD_INVERTDISPLAY:
                tftInvertDisplay( argBoolean );
                break;
            case CMD_DRAWCIRCLEHELPER:
                tftDrawCircleHelper(argXPos, argYPos, argRadius, 
                                    argCornerName, argColor);
                break;
            case CMD_FILLCIRCLEHELPER:
                tftFillCircleHelper(argXPos, argYPos, argRadius, 
                                    argCornerName, argDelta, argColor);
                break;
            case CMD_DRAWBITMAP:
                tftDrawBitmap(argXPos, argYPos, argBitmap, argWidth, 
                              argHeight, argColor);
                break;
            case CMD_DRAWCHAR:
                tftDrawChar(argXPos, argYPos, argChar, argColor, 
                            argBackground, argSize);
                break;
            case CMD_SETCURSOR:
                tftSetCursor( argXPos, argYPos );
                break;
            case CMD_SETTEXTSIZE:
                tftSetTextSize(argSize);
                break;
            case CMD_TFT_HEIGHT:
                tftHeight();
                break;
            case CMD_TFT_WIDTH:
                tftWidth();
                break;
            case CMD_DRAWPIXEL:
                tftDrawPixel(argXPos, argYPos, argColor);
                break;
            case CMD_TFT_PRINT:
            case CMD_TFT_PRINTLN:
                if( argText != NULL )
                {
                    tftPrint_Text( retVal, argText );
                }
                else
                {
                    if( printLongArg == printDoubleArg )
                    {
                        if( printNumArguments == 1 )
                        {
                            tftPrint_Long( retVal, printLongArg );
                        }
                        else
                        {
                            tftPrint_LongFmt( retVal, printLongArg, printArgFmt );
                        }
                    }
                    else
                    {
                        if( printNumArguments == 1 )
                        {
                            tftPrint_Double( retVal, printDoubleArg );
                        }
                        else
                        {
                            tftPrint_DoubleFmt(retVal,printDoubleArg,printArgFmt);
                        }
                    }
                }
                break;
            case CMD_TFT_WRITE:
                tftWrite( argWrite );
                break;
            case CMD_SETTEXTCOLOR:
                switch( setTextColorNumArguments )
                {
                    case 0:
                        Serial.println( "missing color(s)!" );
                        break;
                    case 1:
                        SetTextColor1Arg(argFgColor);
                        break;
                    case 2:
                        SetTextColor2Args(argFgColor, argBgColor);
                        break;
                    default:
                        Serial.println( "too many color(s)!" );
                        break;
                }
                break;
            default:
                break;
        }
    }
    else
    {
        Serial.print( ">" );
        Serial.print( pData );
        Serial.println( "< no command!" );
        retVal = CMD_NONE;
    }

    return( retVal );
}

void setup(void) 
{

    pinMode(TFT_BACKLIGHT, OUTPUT);

#ifdef _SUPPORT_SDCARD_
    pinMode(SD_CS,         OUTPUT);
#endif // _SUPPORT_SDCARD_

#ifdef _SUPPORT_LDR_
    pinMode(LDR_INPUT,     INPUT);
#endif // _SUPPORT_LDR_

    Serial.begin(SERIAL_BAUD);
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);

#ifdef _SUPPORT_IIC_
    Wire.begin(I2C_ADDRESS);       // join i2c bus
    Wire.onReceive(receiveEvent);  // register event
    Wire.onRequest(requestEvent); // register event
#endif // _SUPPORT_IIC_


#ifdef _SUPPORT_SDCARD_

#ifdef SERIAL_DEBUG
    Serial.println();
    Serial.print("Initializing SD card ...");
#endif // SERIAL_DEBUG
    if (!SD.begin(SD_CS)) 
    {
#ifdef SERIAL_DEBUG
        Serial.println("failed!");
#endif // SERIAL_DEBUG
        cardPresent = false;
    }
    else
    {
#ifdef SERIAL_DEBUG
        Serial.println("OK!");
#endif // SERIAL_DEBUG
        cardPresent = true;
    }

#endif // _SUPPORT_SDCARD_

    tft.initR(INITR_BLACKTAB);
    // tft.initR(INITR_144GREENTAB);

#ifdef SERIAL_DEBUG
    Serial.println("TFT initialized");
#endif // SERIAL_DEBUG

    tftBackgroundColor = DEFAULT_BG_COLOR;
    tftForegroundColor = DEFAULT_FG_COLOR;

    tft.fillScreen(tftBackgroundColor);
    tftSetBrightness( DEFAULT_BACKLIGHT );
}


void loop() 
{
    uint16_t  retVal;
    static char result[6];
    static uint32_t lastCheck;
    static uint32_t lastLDRread;

//    if( millis() >= (lastCheck + SD_CHECK_INTVAL) )
//    {
//        if( !cardPresent )
//        {
//            if (SD.begin(SD_CS)) 
//            {
//                Serial.println("sd card OK!");
//                cardPresent = true;
//            }
//        }
//        lastCheck = millis();
//    }
//
//    if( millis() >= (lastLDRread + LDR_CHECK_INTVAL) )
//    {
//        Serial.println( analogRead(LDR_INPUT) );
//        lastLDRread = millis();
//    }
    
    // print the string when a newline arrives:


  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
//    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') 
    {
        retVal = commandParser( inputString );
//        delay(50);

//        Serial.println(inputString);
        Serial.println(retVal);
        inputString = "";

//        stringComplete = true;
    }
    else
    {
      inputString += inChar;
    }
  }


#ifdef NEVERDEF
    
    if (stringComplete) 
    {
        retVal = commandParser( inputString );

#ifdef SERIAL_DEBUG
        Serial.print("executing [");
        Serial.print(inputString);
        Serial.print("], result is");
#endif // SERIAL_DEBUG

        Serial.println(retVal);
        stringComplete = false;
        inputString = "";
    }
#endif NEVERDEF    
}






//  ################### ################# ###################

#ifdef NEVERDEF

sdInit();
sdCardType( void );
sdVolumeInfo( void );
sdListRoot( void );
sdCWD( char *dirname ):
sdListFiles( void );
sdOpenFile( char* pFileName );
sdCloseFile( void );
sdReadChar( void );
sdReadInt16( void );
sdReadInt32( void );
sdReadLine( void );

#define BUFFPIXEL 20

void bmpDraw(char *filename, uint8_t x, uint8_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print("File not found");
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    bmpWidth  = read32(bmpFile);
      bmpDepth = read16(bmpFile); // bits per pixel
        goodBmp = true; // Supported BMP format -- proceed!

        tft.setAddrWindow(x, y, x+w-1, y+h-1);

            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.Color565(r,g,b));

  bmpFile.close();
  if(!goodBmp) Serial.println("BMP format not recognized.");
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}




// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
File myFile;

  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
if (!card.init(SPI_HALF_SPEED, chipSelect)) {
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);




  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
myFile.println("testing 1, 2, 3.");
myFile.close();

  // re-open the file for reading:
myFile = SD.open("test.txt");
if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
myFile.close();

File root;


  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");
}


void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}


File myFile;


  if (SD.exists("example.txt")) {


  // delete the file:
  Serial.println("Removing example.txt...");
  SD.remove("example.txt");

  File dataFile = SD.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();

#endif //

