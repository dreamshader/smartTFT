/*
 ***********************************************************************
 *
 *  smartTFT.h - definitions for an intelligent TFT display class
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

#ifndef SMART_TFT_H
#define SMART_TFT_H

#include "serialConnection.h"

#include <iostream>
#include <string>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <getopt.h>


#ifdef __cplusplus
extern "C" {
#endif
 
using namespace std;

#define CMD_SET_BG              1
#define CMD_SET_FG              2
#define CMD_BRIGHTNESS          3
#define CMD_PRINTTEXT           4
#define CMD_TEXTWRAP            5
#define CMD_SETROTATION         6
#define CMD_CLEAR               7
#define CMD_DRAWTEXT            8
#define CMD_DRAWLINE            9
#define CMD_FAST_H_LINE        10
#define CMD_FAST_V_LINE        11
#define CMD_DRAWRECT           12
#define CMD_FILLRECT           13
#define CMD_DRAWCIRCLE         14
#define CMD_FILLCIRCLE         15
#define CMD_DRAWTRIANGLE       16
#define CMD_FILLTRIANGLE       17
#define CMD_DRAWROUNDRECT      18
#define CMD_FILLROUNDRECT      19
#define CMD_FILLSCREEN         20
#define CMD_INVERTDISPLAY      21
#define CMD_DRAWCIRCLEHELPER   22
#define CMD_FILLCIRCLEHELPER   23
#define CMD_DRAWBITMAP         24
#define CMD_DRAWCHAR           25
#define CMD_SETCURSOR          26
#define CMD_SETTEXTSIZE        27
#define CMD_TFT_HEIGHT         28
#define CMD_TFT_WIDTH          29
#define CMD_DRAWPIXEL          30
#define CMD_TFT_WRITE          31
#define CMD_TFT_PRINT          32
#define CMD_TFT_PRINTLN        33
#define CMD_SETTEXTCOLOR       34


#define DEC                    10
#define HEX                    16
#define OCT                     8
#define BIN                     2

// Color definitions
#define ST7735_BLACK       0x0000
#define ST7735_BLUE        0x001F
#define ST7735_RED         0xF800
#define ST7735_GREEN       0x07E0
#define ST7735_CYAN        0x07FF
#define ST7735_MAGENTA     0xF81F
#define ST7735_YELLOW      0xFFE0
#define ST7735_WHITE       0xFFFF

#define SEND_BUFFER_SIZE     1024
#define RESPONSE_BUFFER_SIZE 1024

class smartTFT {

  private:
    serialConnection             *connection;

//  int16_t height(void),
//  int16_t width(void);
//  uint8_t getRotation(void);


  public:
//    smartTFT(void) {  connection = new serialConnection(); };

    smartTFT( char *devname = (char*) DEFAULT_DEVICE, 
              uint32_t baud = DEFAULT_BAUD, 
              int16_t databits = DEFAULT_DATABIT, 
              int8_t parity = DEFAULT_PARITY, 
              int16_t stopbits = DEFAULT_STOPBITS, 
              int8_t handshake = DEFAULT_HANDSHAKE )
        {
            connection = new serialConnection( devname, baud,
                          databits, parity, stopbits, handshake );
        }

  protected:
    int8_t connectiontype;

    int16_t _width,     _height;
    int16_t _cursor_x,  _cursor_y;
    int16_t _textcolor, _bgcolor;
    uint8_t _textsize;
    uint8_t _rotation;
    bool    _wrap;


  public:
    uint8_t commandBuffer[SEND_BUFFER_SIZE];
    uint8_t responseBuffer[RESPONSE_BUFFER_SIZE];

    int setup( char *devname, uint32_t baud, int16_t databits,
               int8_t parity, int16_t stopbits, int8_t handshake );

    int connect( char *devname, uint32_t baud, int16_t databits,
               int8_t parity, int16_t stopbits, int8_t handshake );

    int connect( void );
    int disconnect( void );

    int16_t tft_height( void );
    int16_t tft_width( void );
    int16_t sendRequest( void );
    int16_t getResponse( void );
    int16_t flushSerial( void );

    int16_t tft_drawPixel(int16_t x, int16_t y, uint16_t color);
    int16_t tft_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
                     uint16_t color);
    int16_t tft_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    int16_t tft_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    int16_t tft_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    int16_t tft_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    int16_t tft_fillScreen(uint16_t color);
    int16_t tft_invertDisplay(bool i);
    int16_t tft_setCursor(int16_t x, int16_t y);
    int16_t tft_setTextColor(uint16_t c);
    int16_t tft_setTextColor(uint16_t c, uint16_t bg);
    int16_t tft_setTextSize(int8_t newsize);
    int16_t tft_setTextWrap(bool w);
    int16_t tft_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    int16_t tft_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    int16_t tft_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                         int16_t x2, int16_t y2, uint16_t color);
    int16_t tft_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                          int16_t radius, uint16_t color);
    int16_t tft_setTextSize(uint8_t s);
    int16_t tft_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                         int16_t x2, int16_t y2, uint16_t color);
    int16_t tft_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                          int16_t radius, uint16_t color);
    int16_t tft_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, 
                             uint8_t cornername, uint16_t color);
    int16_t tft_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, 
                             uint8_t cornername, int16_t delta, uint16_t color);
    int16_t tft_drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
                       int16_t w, int16_t h, uint16_t color);
    int16_t tft_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
                     uint16_t bg, uint8_t size);
    int16_t tft_setRotation(uint8_t r);

    size_t tft_print(string data);
    size_t tft_print(const char data[]);
    size_t tft_print(char data);
    size_t tft_print(unsigned char data, int fmt = DEC);
    size_t tft_print(int data, int fmt = DEC);
    size_t tft_print(unsigned int data, int fmt = DEC);
    size_t tft_print(long data, int fmt = DEC);
    size_t tft_print(unsigned long data, int fmt = DEC);
    size_t tft_print(double data, int fmt = 2);

    size_t tft_println(string data);
    size_t tft_println(const char data[]);
    size_t tft_println(char data);
    size_t tft_println(unsigned char data, int fmt = DEC);
    size_t tft_println(int data, int fmt = DEC);
    size_t tft_println(unsigned data, int fmt = DEC);
    size_t tft_println(long data, int fmt = DEC);
    size_t tft_println(unsigned long data, int fmt = DEC);
    size_t tft_println(double data, int fmt = 2);
    size_t tft_println(void);

};


#ifdef __cplusplus
}
#endif

#endif // SMART_TFT_H

#ifdef RESERVE

size_t Print::print(const __FlashStringHelper *ifsh)
{
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  size_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    if (write(c)) n++;
    else break;
  }
  return n;
}

size_t Print::print(const String &s)
{
  return write(s.c_str(), s.length());
}

size_t Print::print(const char str[])
{
  return write(str);
}

size_t Print::print(char c)
{
  return write(c);
}

size_t Print::print(unsigned char b, int16_t base)
{
  return print((unsigned long) b, base);
}

size_t Print::print(int16_t n, int16_t base)
{
  return print((long) n, base);
}

size_t Print::print(unsigned int16_t n, int16_t base)
{
  return print((unsigned long) n, base);
}

size_t Print::print(long n, int16_t base)
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int16_t t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

size_t Print::print(unsigned long n, int16_t base)
{
  if (base == 0) return write(n);
  else return printNumber(n, base);
}

size_t Print::print(double n, int16_t digits)
{
  return printFloat(n, digits);
}

size_t Print::println(const __FlashStringHelper *ifsh)
{
  size_t n = print(ifsh);
  n += println();
  return n;
}

size_t Print::print(const Printable& x)
{
  return x.printTo(*this);
}

size_t Print::println(void)
{
  return write("\r\n");
}

size_t Print::println(const String &s)
{
  size_t n = print(s);
  n += println();
  return n;
}

size_t Print::println(const char c[])
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(char c)
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(unsigned char b, int16_t base)
{
  size_t n = print(b, base);
  n += println();
  return n;
}

size_t Print::println(int16_t num, int16_t base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned int16_t num, int16_t base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(long num, int16_t base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned long num, int16_t base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(double num, int16_t digits)
{
  size_t n = print(num, digits);
  n += println();
  return n;
}

size_t Print::println(const Printable& x)
{
  size_t n = print(x);
  n += println();
  return n;
}

// Private Methods /////////////////////////////////////////////////////////////

size_t Print::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return write(str);
}

size_t Print::printFloat(double number, uint8_t digits) 
{ 
  size_t n = 0;
  
  if (isnan(number)) return print("nan");
  if (isinf(number)) return print("inf");
  if (number > 4294967040.0) return print16_t ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print16_t ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     n += print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print16_t it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print16_t the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print('.'); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int16_t toPrint16_t = (unsigned int)(remainder);
    n += print(toPrint);
    remainder -= toPrint; 
  } 
  
  return n;
}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <getopt.h>

// a simple tcp/ip client in 100 lines ...
// (C) 2015 Dreamshader 
// This source is in the public domain and may be used
// without any restrictions.
//
// to compile simply type:
//                 make simple_tcp_client
//
//


// number of write attempts
#define NUMBER_OF_WRITES   3


//
// Retrieve given command-line arguments
//
// function arguments:
//   int16_t argc           argc passed from main
//   char **argv        argv passed from main
//   int16_t *pPort         a pointer to our port-variable
//   char **pHostname   a pointer to our hostname-variable
//
void getArguments ( int16_t argc, char **argv, int16_t *pPort, char **pHostname )
{
  int16_t next_option;

  /* valid short options letters */
  const char* const short_options = "p:h:?";

  /* valid long options */
  const struct option long_options[] = {
      { "port",		1, NULL, 'p' },
      { "hostname",	1, NULL, 'h' },
      { "help",		0, NULL, '?' },
      { NULL,		0, NULL,  0  }
  };

  *pHostname = NULL;
  *pPort = -1;

  while( (next_option = getopt_long (argc, argv,
                        short_options, long_options, NULL)) != -1 )
  {
    switch( next_option )
    {
      // port
      case 'p':
        *pPort = atoi(optarg);
        break;
      // hostname
      case 'h':
        *pHostname = optarg;
        break;
      case '?':
        fprintf(stderr,"usage: %s -h host -p port\n", argv[0]);
        break;
      default:
        fprintf(stderr, "Invalid option %c! \n", next_option);
        break;
    }
  }
}

int16_t main(int16_t argc, char *argv[])
{
    char buffer[4096];
    int16_t sockfd, port;
    char *hostname;
    struct sockaddr_in serverAddr;
    struct hostent *server;
    int16_t i, n;

    if (argc < 3) 
    {
       fprintf(stderr,"usage: %s -h host -p port\n", argv[0]);
    }
    else
    {
        // retrieve given arguments ...
        getArguments( argc, argv, &port, &hostname );

        // hostname and port must be set!
        // getArguments sets hostname to point16_t to NULL 
        // and port to -1. So we can detect, whether arguments
        // are given or not.
        if( hostname == NULL || port == -1 )
        {
            fprintf(stderr,"usage: %s -h host -p port\n", argv[0]);
        }
        else
        {
            // create a INET socket.
            if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
            {
                perror("socket failed");
            }
            else
            {
                //get address info for hostname
                if( (server = gethostbyname(hostname)) == NULL )
                {
                    fprintf(stderr,"host %s not found!\n", hostname);
                }
                else
                {
                    // initialize address
                    bzero((char *) &serverAddr, sizeof(serverAddr));
                    // protocol family is INET
                    serverAddr.sin_family = AF_INET;
                    // copy host address to structure
                    bcopy((char *)server->h_addr, 
                          (char *)&serverAddr.sin_addr.s_addr, 
                          server->h_length);
                    // port number must be in network byte order
                    serverAddr.sin_port = htons(port);

                    // now try to connect to server ...
                    if (connect(sockfd,
                                (struct sockaddr *) &serverAddr,
                                sizeof(serverAddr)) < 0)
                    {
                        perror("connecting failed");
                    }
                    else
                    {
                        // we are connected sucessfully
                        printf("connected to server %s\n", hostname);

                        for (i = 0; i < NUMBER_OF_WRITES; ++i)
                        {
                            printf("Enter message %d: ", i+1);
                            // reset buffer content
                            bzero(buffer,sizeof(buffer));
                            // read until <ENTER>
                            fgets(buffer,sizeof(buffer),stdin);

                            if( (n = write(sockfd,buffer,strlen(buffer))) < 0 )
                            {
                                perror("write failed");
                            }
                            else
                            {
                                printf("sent %d bytes: %s", n, buffer);
                                // reset buffer content
                                bzero(buffer,sizeof(buffer));
                                // read response from server
                                if( (n = read( sockfd, buffer,
                                               sizeof(buffer)) ) < 0 )
                                {
                                    perror("read response failed");
                                }
                                else
                                {
                                    printf("response of %d bytes received: %s",
                                           n, buffer);
                                }
                            }
                        }
                    }
                }
                close(sockfd);
            }
        }
    }
}

#endif // RESERVE
