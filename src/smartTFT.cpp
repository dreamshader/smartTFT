/*
 ***********************************************************************
 *
 *  smartTFT.cpp - a class for an intelligent TFT display
 *
 *  Copyright (C) 2018 Dreamshader (aka Dirk Schanz)
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  
 *      http://www.apache.org/licenses/LICENSE-2.0
 *  
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ***********************************************************************
 */

#include "smartTFT.h"
#include "serialConnection.h"

#define ERR_FAIL    -1


/* ----------------------------------------------------------------------------
 * int16_t getResponse( void )
 *
 * read the response of the attached smart-TFT into responseBuffer
 * returns the amount if characters read or an error code
 ------------------------------------------------------------------------------
*/
int16_t smartTFT::getResponse( void )
{
    int retVal;

    if( connection != NULL )
    {
        retVal = (int16_t) connection->ser_read( (char*) responseBuffer,
                                                 RESPONSE_BUFFER_SIZE-1 );
    }
    else
    {
        retVal = E_NULL_CONNECTION;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int16_t sendRequest( void )
 *
 * send the command buffer to the attached smart-TFT
 * returns the amount if characters written or an error code
 ------------------------------------------------------------------------------
*/
int16_t smartTFT::sendRequest( void )
{
    int retVal;

printf("command >%s<", commandBuffer);

    if( connection != NULL )
    {
        retVal = (int16_t) connection->ser_write( (char*) commandBuffer,
                                                 strlen((char*) commandBuffer) );
        if( retVal > 0 )
        {
            retVal = getResponse();
        }
printf("response [%s]\n", responseBuffer);
    }
    else
    {
        retVal = E_NULL_CONNECTION;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int16_t tft_height( void )
 *
 * get height of attached smart-TFT
 ------------------------------------------------------------------------------
*/
int16_t smartTFT::tft_height( void )
{
    return(_height);
}

/* ----------------------------------------------------------------------------
 * int16_t tft_width( void )
 *
 * get width of attached smart-TFT
 ------------------------------------------------------------------------------
*/
int16_t smartTFT::tft_width( void )
{

    return(_width);
}

/* ----------------------------------------------------------------------------
 * int setup( char *devname, uint32_t baud, int16_t databits,
 *              int8_t parity, int16_t stopbits, int8_t handshake )
 *
 * setup connection parameters to given values
 * return E_OK on succes, otherwise an error code
 ------------------------------------------------------------------------------
*/
int smartTFT::setup( char *devname, uint32_t baud, int16_t databits,
                 int8_t parity, int16_t stopbits, int8_t handshake )
{
    int retVal;

    if( connection != NULL )
    {
        retVal = (int) connection->setup( devname, baud, databits,
                           parity, stopbits, handshake );
    }
    else
    {
        retVal = E_NULL_CONNECTION;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int connect( char *devname, uint32_t baud, int16_t databits,
 *              int8_t parity, int16_t stopbits, int8_t handshake )
 *
 * connect to an attached smart-TFT using given parameters
 * return E_OK on succes, otherwise an error code
 ------------------------------------------------------------------------------
*/
int smartTFT::connect( char *devname, uint32_t baud, int16_t databits,
                 int8_t parity, int16_t stopbits, int8_t handshake )
{
    int retVal;

    if( connection != NULL )
    {
        retVal = (int) connection->ser_open( devname, baud, databits,
                           parity, stopbits, handshake );
    }
    else
    {
        retVal = E_NULL_CONNECTION;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int connect( void )
 *
 * connect to an attached smart-TFT
 * return E_OK on succes, otherwise an error code
 ------------------------------------------------------------------------------
*/
int smartTFT::connect( void )
{
    int retVal;

    if( connection != NULL )
    {
        retVal = (int) connection->ser_open( );
    }
    else
    {
        retVal = E_NULL_CONNECTION;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int disconnect( void )
 *
 * close connection to attached smart-TFT
 * return E_OK on succes, otherwise an error code
 ------------------------------------------------------------------------------
*/
int smartTFT::disconnect( void )
{
    int retVal;

    if( connection != NULL )
    {
        retVal = (int) connection->ser_close( );
    }
    else
    {
        retVal = E_NULL_CONNECTION;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int16_t tft_drawPixel(int16_t x, int16_t y, uint16_t color)
 *
 * send request for GFX-function drawPixel with given parameter to TFT
 * return E_OK on succes, otherwise an error code
 ------------------------------------------------------------------------------
*/
int16_t smartTFT::tft_drawPixel(int16_t x, int16_t y, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %u)\n", CMD_DRAWPIXEL, x, y, color);
    return( sendRequest() );
}

/* ----------------------------------------------------------------------------
 * int16_t tft_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
 *                      uint16_t color)
 *
 * send request for GFX-function drawLine with given parameter to TFT
 * return E_OK on succes, otherwise an error code
 ------------------------------------------------------------------------------
*/
int16_t smartTFT::tft_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
                     uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %u)\n", CMD_DRAWLINE, x0, y0, x1, y1, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %u)\n", CMD_FAST_V_LINE, x, y, h, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %u)\n", CMD_FAST_H_LINE, x, y, w, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %u)\n", CMD_DRAWRECT, x, y, w, h, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %u)\n", CMD_FILLRECT, x, y, w, h, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_fillScreen(uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%u)\n", CMD_FILLSCREEN, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_invertDisplay(bool invert)
{
    sprintf((char*) commandBuffer, "f%d(%d)\n", CMD_INVERTDISPLAY, invert);
    return( sendRequest() );
}

int16_t smartTFT::tft_setCursor(int16_t x, int16_t y)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d)\n", CMD_SETCURSOR, x, y);
    return( sendRequest() );
}

int16_t smartTFT::tft_setTextColor(uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%u)\n", CMD_SETTEXTCOLOR, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_setTextColor(uint16_t color, uint16_t background)
{
    sprintf((char*) commandBuffer, "f%d(%u, %u)\n", CMD_SETTEXTCOLOR, color, background);
    return( sendRequest() );
}

int16_t smartTFT::tft_setTextWrap(bool wrap)
{
    sprintf((char*) commandBuffer, "f%d(%d)\n", CMD_TEXTWRAP, wrap);
    return( sendRequest() );
}

int16_t smartTFT::tft_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %u)\n", CMD_FILLCIRCLE, x0, y0, r, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %u)\n", CMD_DRAWCIRCLE, x0, y0, r, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                         int16_t x2, int16_t y2, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %d, %d, %u)\n", CMD_DRAWTRIANGLE, x0, y0, x1, y1, x2, y2, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                          int16_t radius, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %d, %u)\n", CMD_DRAWROUNDRECT, x0, y0, w, h, radius, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_setTextSize(uint8_t size)
{
    sprintf((char*) commandBuffer, "f%d(%d)\n", CMD_SETTEXTSIZE, size);
    return( sendRequest() );
}

int16_t smartTFT::tft_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                         int16_t x2, int16_t y2, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %d, %d, %u)\n", CMD_FILLTRIANGLE, x0, y0, x1, y1, x2, y2, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                          int16_t radius, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %d, %u)\n", CMD_FILLROUNDRECT, x0, y0, w, h, radius, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, 
                             uint8_t cornername, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %u)\n", CMD_DRAWCIRCLEHELPER, x0, y0, r, cornername, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, 
                             uint8_t cornername, int16_t delta, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %d, %d, %d, %u)\n", CMD_FILLCIRCLEHELPER, x0, y0, r, cornername, delta, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
                       int16_t w, int16_t h, uint16_t color)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, \"%s\", %d, %d, %u)\n", CMD_DRAWBITMAP, x, y, bitmap, w, h, color);
    return( sendRequest() );
}

int16_t smartTFT::tft_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
                     uint16_t background, uint8_t size)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d, %c, %u, %u, %d)\n", CMD_DRAWCHAR, x, y, c, color, background, size);
    return( sendRequest() );
}

int16_t smartTFT::tft_setRotation(uint8_t rotation)
{
    sprintf((char*) commandBuffer, "f%d(%d)\n", CMD_SETROTATION, rotation);
    return( sendRequest() );
}

int16_t smartTFT:: tft_setTextSize(int8_t newsize)
{
    sprintf((char*) commandBuffer, "f%d(%d)\n", CMD_SETTEXTSIZE, newsize);
    return( sendRequest() );
}

size_t smartTFT::tft_print(const string data)
{
    sprintf((char*) commandBuffer, "f%d(\"%s\")\n", CMD_TFT_PRINT, data.c_str());
    return( sendRequest() );
}

size_t smartTFT::tft_print(const char data[])
{
    sprintf((char*) commandBuffer, "f%d(\"%s\")\n", CMD_TFT_PRINT, data);
    return( sendRequest() );
}

size_t smartTFT::tft_print(char data)
{
    sprintf((char*) commandBuffer, "f%d(%c)\n", CMD_TFT_PRINT, data);
    return( sendRequest() );
}

size_t smartTFT::tft_print(unsigned char data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%u, %d)\n", CMD_TFT_PRINT, data, fmt);
    return( sendRequest() );
}

size_t smartTFT::tft_print(int data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d)\n", CMD_TFT_PRINT, data, fmt);
    return( sendRequest() );
}

size_t smartTFT::tft_print(unsigned int data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%u, %d)\n", CMD_TFT_PRINT, data, fmt);
    return( sendRequest() );
}

size_t smartTFT::tft_print(long data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%ld, %d)\n", CMD_TFT_PRINT, data, fmt);
    return( sendRequest() );
}

size_t smartTFT::tft_print(unsigned long data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%lu, %d)\n", CMD_TFT_PRINT, data, fmt);
    return( sendRequest() );
}

size_t smartTFT::tft_print(double data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%f, %d)\n", CMD_TFT_PRINT, data, fmt);
    return( sendRequest() );
}


size_t smartTFT::tft_println(const string data)
{
    sprintf((char*) commandBuffer, "f%d(\"%s\")\n", CMD_TFT_PRINTLN, data.c_str());
    return( sendRequest() );
}

size_t smartTFT::tft_println(const char data[])
{
    sprintf((char*) commandBuffer, "f%d(\"%s\")\n", CMD_TFT_PRINTLN, data);
tft_println();
    return( sendRequest() );
}

size_t smartTFT::tft_println(char data)
{
    sprintf((char*) commandBuffer, "f%d(%c)\n", CMD_TFT_PRINTLN, data);
tft_println();
    return( sendRequest() );
}

size_t smartTFT::tft_println(unsigned char data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%u, %d)\n", CMD_TFT_PRINTLN, data, fmt);
tft_println();
    return( sendRequest() );
}

size_t smartTFT::tft_println(int data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%d, %d)\n", CMD_TFT_PRINTLN, data, fmt);
tft_println();
    return( sendRequest() );
}

size_t smartTFT::tft_println(unsigned int data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%u, %d)\n", CMD_TFT_PRINTLN, data, fmt);
tft_println();
    return( sendRequest() );
}

size_t smartTFT::tft_println(long data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%ld, %d)\n", CMD_TFT_PRINTLN, data, fmt);
tft_println();
    return( sendRequest() );
}

size_t smartTFT::tft_println(unsigned long data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%lu, %d)\n", CMD_TFT_PRINTLN, data, fmt);
tft_println();
    return( sendRequest() );
}

size_t smartTFT::tft_println(double data, int fmt)
{
    sprintf((char*) commandBuffer, "f%d(%f, %d)\n", CMD_TFT_PRINTLN, data, fmt);
tft_println();
    return( sendRequest() );
}

size_t smartTFT::tft_println(void)
{
    sprintf((char*) commandBuffer, "f%d(\"\n\")\n", CMD_TFT_PRINTLN);
    return( sendRequest() );
}



#ifdef NEVERDEF
int16_t smartTFT::connect(void) 
{ 

    return( sendRequest() );
}

int16_t smartTFT::connect(int16_t connType) 
{

    _connectiontype = connType; 

    return( sendRequest() );
}

int16_t smartTFT::connect(int16_t connType, char *pdevice) 
{ 

    _connectiontype = connType; 
    _pInterface = strdup( pdevice );

    return( sendRequest() );
}

int16_t smartTFT::connect(int16_t connType, char *pdevice, uint32_t speed) 
{ 

    _connectiontype = connType; 
    _pInterface = strdup( pdevice );
    _baud = speed;

    return( sendRequest() );
}

int16_t smartTFT::connect(int16_t connType, char *pdevice, uint32_t speed, 
                          char parity) 
{ 

    _connectiontype = connType; 
    _pInterface = strdup( pdevice );
    _baud = speed;
    _parity = parity;

    return( sendRequest() );
}

int16_t smartTFT::connect(int16_t connType, char *pdevice, uint32_t speed, 
                          char parity, int8_t databits) 
{ 

    _connectiontype = connType; 
    _pInterface = strdup( pdevice );
    _baud = speed;
    _parity = parity;
    _databits = databits;

    return( sendRequest() );
}

int16_t smartTFT::connect(int16_t connType, char *pdevice, uint32_t speed, 
                          char parity, int8_t databits, int8_t stopbits) 
{ 

    _connectiontype = connType; 
    _pInterface = strdup( pdevice );
    _baud = speed;
    _parity = parity;
    _databits = databits;
    _stopbits = stopbits;

    return( sendRequest() );
}

int16_t smartTFT::closeConnection( void )
{

    return( sendRequest() );
}

int16_t smartTFT::disconnect( void )
{

    return( sendRequest() );
}

#endif // NEVERDEF





