/*
 ***********************************************************************
 *
 *  graphicstest.cpp - a simple test for smartTFT class
 *
 *  this program is a port of the graphicstest example of the
 *  Adafruit ST7735 library.
 *
 ***********************************************************************
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
 *
 * Options:
 *
 * -------------- communication port for connection --------------------
 *
 * --com devicename (same as --com=devicename resp. -c devicename)
 *
 *   Default is --com=/dev/ttyUSB0
 *
 * ---------------- baudrate for serial connection ---------------------
 *
 * --baud baudrate (same as --baud=baudrate resp. -b baudrate)
 *
 *   Default is --baud=38400
 *
 * ---------------- databit for serial connection ----------------------
 *
 * --data bits (same as --data=bits resp. -d bits)
 *			may be 5 up to 8
 *
 *   Default is --data=8
 *
 * ---------------- parity for serial connection -----------------------
 *
 * --parity parity (same as --parity=parity resp. -p parity)
 *			may be e/E (even), o/O (odd), n/N (none)
 *
 *   Default is --parity=n
 *
 * --------------- stoppbits for serial connection ---------------------
 *
 * --stop stoppbits (same as --stop=stoppbits resp. -s stoppbits)
 *			may be 1 or 2
 *
 *   Default is --stop=1
 *
 * --------------- handshake for serial connection ---------------------
 *
 * --handshake handshake (same as --handshake=handshake resp. -h handshake)
 *			may be n/N (no handshake), x/X (XON/XOFF)
 *
 *   Default is --handshake=n
 *
 * ----------------------------- help ----------------------------------
 *
 * --help 	(same as -? )
 *
 *   Show options and exit
 *
 ***********************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/param.h>
#include <fcntl.h>
#include <termios.h>



#include <iostream>
#include <string>

#include "smartTFT.h"

float p = 3.1415926;
smartTFT *display;

void testlines(uint16_t color) {
  display->tft_fillScreen(ST7735_BLACK);

  for (int16_t x=0; x < display->tft_width(); x+=6) {
    display->tft_drawLine(0, 0, x, display->tft_height()-1, color);

  }
  for (int16_t y=0; y < display->tft_height(); y+=6) {
    display->tft_drawLine(0, 0, display->tft_width()-1, y, color);

  }

  display->tft_fillScreen(ST7735_BLACK);

  for (int16_t x=0; x < display->tft_width(); x+=6) {
    display->tft_drawLine(display->tft_width()-1, 0, x, display->tft_height()-1, color);

  }
  for (int16_t y=0; y < display->tft_height(); y+=6) {
    display->tft_drawLine(display->tft_width()-1, 0, 0, y, color);

  }

  display->tft_fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < display->tft_width(); x+=6) {
    display->tft_drawLine(0, display->tft_height()-1, x, 0, color);

  }
  for (int16_t y=0; y < display->tft_height(); y+=6) {
    display->tft_drawLine(0, display->tft_height()-1, display->tft_width()-1, y, color);

  }

  display->tft_fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < display->tft_width(); x+=6) {
    display->tft_drawLine(display->tft_width()-1, display->tft_height()-1, x, 0, color);

  }
  for (int16_t y=0; y < display->tft_height(); y+=6) {
    display->tft_drawLine(display->tft_width()-1, display->tft_height()-1, 0, y, color);

  }
}

void testdrawtext(char *text, uint16_t color) {
  display->tft_setCursor(0, 0);

  display->tft_setTextColor(color);

  display->tft_setTextWrap(true);

  display->tft_print(text);

}

void testfastlines(uint16_t color1, uint16_t color2) {
  display->tft_fillScreen(ST7735_BLACK);

  for (int16_t y=0; y < display->tft_height(); y+=5) {
    display->tft_drawFastHLine(0, y, display->tft_width(), color1);

  }
  for (int16_t x=0; x < display->tft_width(); x+=5) {
    display->tft_drawFastVLine(x, 0, display->tft_height(), color2);

  }
}

void testdrawrects(uint16_t color) {
  display->tft_fillScreen(ST7735_BLACK);

  for (int16_t x=0; x < display->tft_width(); x+=6) {
    display->tft_drawRect(display->tft_width()/2 -x/2, display->tft_height()/2 -x/2 , x, x, color);

  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  display->tft_fillScreen(ST7735_BLACK);

  for (int16_t x=display->tft_width()-1; x > 6; x-=6) {
    display->tft_fillRect(display->tft_width()/2 -x/2, display->tft_height()/2 -x/2 , x, x, color1);

    display->tft_drawRect(display->tft_width()/2 -x/2, display->tft_height()/2 -x/2 , x, x, color2);

  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < display->tft_width(); x+=radius*2) {
    for (int16_t y=radius; y < display->tft_height(); y+=radius*2) {
      display->tft_fillCircle(x, y, radius, color);

    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < display->tft_width()+radius; x+=radius*2) {
    for (int16_t y=0; y < display->tft_height()+radius; y+=radius*2) {
      display->tft_drawCircle(x, y, radius, color);

    }
  }
}

void testtriangles() {
  display->tft_fillScreen(ST7735_BLACK);

  int color = 0xF800;
  int t;
  int w = display->tft_width()/2;

  int x = display->tft_height()-1;

  int y = 0;
  int z = display->tft_width();

  for(t = 0 ; t <= 15; t++) {
    display->tft_drawTriangle(w, y, y, x, z, x, color);

//    usleep(5000);

    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  display->tft_fillScreen(ST7735_BLACK);

  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = display->tft_width()-2;

    int h = display->tft_height()-2;

    for(i = 0 ; i <= 16; i+=1) {
      display->tft_drawRoundRect(x, y, w, h, 5, color);

//      usleep(5000);

      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  display->tft_setTextWrap(false);

  display->tft_fillScreen(ST7735_BLACK);

  display->tft_setCursor(0, 30);

  display->tft_setTextColor(ST7735_RED);

  display->tft_setTextSize((uint8_t) 1);

  display->tft_println("Hello World!");

  display->tft_setTextColor(ST7735_YELLOW);

  display->tft_setTextSize((uint8_t) 2);

  display->tft_println("Hello World!");

  display->tft_setTextColor(ST7735_GREEN);

  display->tft_setTextSize((uint8_t) 3);

  display->tft_println("Hello World!");

  display->tft_setTextColor(ST7735_BLUE);

  display->tft_setTextSize((uint8_t) 4);

  display->tft_print(1234.567);

  display->tft_setCursor(0, 0);

  display->tft_fillScreen(ST7735_BLACK);

  display->tft_setTextColor(ST7735_WHITE);

  display->tft_setTextSize((uint8_t) 0);

  display->tft_println("Hello World!");

  display->tft_setTextSize((uint8_t) 1);

  display->tft_setTextColor(ST7735_GREEN);

  display->tft_print(p, 6);

  display->tft_println(" Want pi?");

  display->tft_println(" ");

  display->tft_print(8675309, HEX); // print 8,675,309 out in HEX!

  display->tft_println(" Print HEX!");

  display->tft_println(" ");

  display->tft_setTextColor(ST7735_WHITE);

  display->tft_println("Sketch has been");

  display->tft_println("running for: ");

  display->tft_setTextColor(ST7735_MAGENTA);

  display->tft_setTextColor(ST7735_WHITE);

  display->tft_print(" seconds.");

}

void mediabuttons() {
  // play
  display->tft_fillScreen(ST7735_BLACK);

  display->tft_fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);

  display->tft_fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);

  // pause
  display->tft_fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);

  display->tft_fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);

  display->tft_fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);

  // play color
  display->tft_fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);

  // pause color
  display->tft_fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);

  display->tft_fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);

  // play color
  display->tft_fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);

}





#define COMPORT			"/dev/ttyUSB0"
#define E_BAUDRATE	-10
#define E_DATABIT		-11
#define E_PARITY		-12
#define E_STOPPBITS	-13
#define E_HANDSHAKE	-14
#define E_DEVICE		-15
#define E_NULL		-16
#define E_NOFD		-17




typedef struct serial_param_t {
char *device;
int dev_fd;
struct termios oldtio;
struct termios rawtio;
unsigned int baud;
unsigned char databit;
unsigned char parity;
unsigned char stoppbits;
unsigned char handshake;
} serial_param;






/* ---------------------------------------------------------------------------------
 | void set_defaults( struct serial_param_t *ctl_param )
 |
 | clear structure and set defaults
 -----------------------------------------------------------------------------------
*/

void set_defaults( struct serial_param_t *ctl_param )
{
	if( ctl_param != NULL )
	{
		ctl_param->device = (char*) COMPORT;
		ctl_param->baud = 38400;
		ctl_param->databit = 8;
		ctl_param->parity = 'N';
		ctl_param->stoppbits = 1;
		ctl_param->handshake = 'N';
	}

	return;
}







/* ---------------------------------------------------------------------------------
 | void help( struct serial_param_t *ctl_param, short failed )
 |
 | show options. If failed, print an error message, too
 -----------------------------------------------------------------------------------
*/

void help( struct serial_param_t *ctl_param, short failed )
{

	fprintf(stderr, "soehnle printer on RPi\n");
	fprintf(stderr, "valid options are:\n");
	fprintf(stderr, 
		"--com devicename (same as --com=devicename resp. -c devicename)\n");
	fprintf(stderr, "use device devicename\n");
	fprintf(stderr, "Default is --com=/dev/ttyUSB0\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "--baud baudrate (same as --baud=baudrate resp. -b baudrate)\n");
	fprintf(stderr, "set speed to baudrate\n");
	fprintf(stderr, "Default is --baud=38400\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "--data bits (same as --data=bits resp. -d bits)\n");
	fprintf(stderr, "set databits to bits (5 up to 8 )\n");
	fprintf(stderr, "Default is --data=8\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "--parity parity (same as --parity=parity resp. -p parity)\n");
	fprintf(stderr, 
		"which parity to use (e/E for even, o/O for odd, n/N for no parity check)\n");
	fprintf(stderr, "Default is --parity=n\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "--stop stoppbits (same as --stop=stoppbits resp. -s stoppbits)\n");
	fprintf(stderr, "amount of stoppbits ( 1 or 2 )\n");
	fprintf(stderr, "Default is --stop=1\n");
	fprintf(stderr, "\n");
	fprintf(stderr, 
		"--handshake handshake (same as --handshake=handshake resp. -h handshake)\n");
	fprintf(stderr, "handshake for transmission (n/N for none, x/X for ixon/ixoff)\n");
	fprintf(stderr, "Default is --handshake=n\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "--help 	(same as -? )\n");
	fprintf(stderr, "display help info\n");

	exit(failed);
}

/* ---------------------------------------------------------------------------------
 | void get_arguments ( int argc, char **argv, struct serial_param_t *ctl_param, 
 |                      short *myst)
 |
 | scan commandline for arguments an set the corresponding value
 | myst is a short pointer to a secret flag
 -----------------------------------------------------------------------------------
*/

void get_arguments ( int argc, char **argv, struct serial_param_t *ctl_param, short *myst)
{

	int failed = 0;
	int next_option;
	/* valid short options letters */
	const char* const short_options = "c:b:d:p:s:h:m?";

	/* valid long options */
	const struct option long_options[] = {
 		{ "com",		1, NULL, 'c' },
 		{ "baud",		1, NULL, 'b' },
 		{ "data",		1, NULL, 'd' },
 		{ "parity",		1, NULL, 'p' },
 		{ "stop",		1, NULL, 's' },
 		{ "handshake",		1, NULL, 'h' },
 		{ "mystery",		0, NULL, 'm' },
 		{ "help",		0, NULL, '?' },
		{ NULL,			0, NULL,  0  }
	};

	set_defaults( ctl_param );
	if( myst != NULL )
	{
		*myst = 0;
	}
	failed = 0;

	do
	{
		next_option = getopt_long (argc, argv, short_options,
			long_options, NULL);

		switch (next_option) {
			case 'c':
				if( strlen(optarg) )
				{
					ctl_param->device = strdup( optarg );
				}
				else
				{
					help( ctl_param, E_DEVICE);
				}
				break;
			case 'b':
				ctl_param->baud = atoi(optarg);
				break;
			case 'd':
				ctl_param->databit =atoi(optarg);
				break;
			case 'p':
				ctl_param->parity = optarg[0];
				break;
			case 's':
				ctl_param->stoppbits =atoi(optarg);
				break;
			case 'h':
				ctl_param->handshake = optarg[0];
				break;
			case 'm':
				if( myst != NULL )
				{
					*myst = 1;
				}
				break;
			case '?':
				help( ctl_param, 0 );
				break;
			case -1:
				break;
			default:
				fprintf(stderr, "Invalid option %c! \n", next_option);
				help( ctl_param, 0 );
		}
	} while (next_option != -1);
}


/* ---------------------------------------------------------------------------------
 | int check_param( struct serial_param_t *ctl_param )
 |
 | Check parameters for validity
 | return an error code depending on the invalid parameter
 -----------------------------------------------------------------------------------
*/

int check_param( struct serial_param_t *ctl_param )
{
	int fail = 0;

	if( ctl_param != NULL )
	{
		if( access( ctl_param->device, F_OK) == 0)
		{
			switch( ctl_param->baud )
			{
				case     50:
				case     75:
				case    110:
				case    134:
				case    150:
				case    200:
				case    300:
				case    600 :
				case   1200:
				case   1800:
				case   2400:
				case   4800:
				case   9600:
				case  19200:
				case  38400:
				case  57600:
				case 115200:
				case 230400:
				case 460800:
					break;
				default:
					fail = E_BAUDRATE;
			}

			switch( ctl_param->databit )
			{
				case 5:
				case 6:
				case 7:
				case 8:
					break;
				default:
					fail = E_DATABIT;
			}

			switch( ctl_param->parity )
			{
				case 'o':
				case 'O':
				case 'e':
				case 'E':
				case 'n':
				case 'N':
					break;
				default:
					fail = E_PARITY;
			}

			switch( ctl_param->stoppbits )
			{
				case 1:
				case 2:
					break;
				default:
					fail = E_STOPPBITS;
			}

			switch( ctl_param->handshake )
			{
				case 'n':
				case 'N':
				case 'x':
				case 'X':
					break;
				default:
					fail = E_HANDSHAKE;
			}
		}
		else
		{
			fail = E_DEVICE;
		}
	}
	else
	{
		fail = E_NULL;
	}

	return( fail );
}














































int main( int argc, char *argv[] )
{
    int retVal = 0;
    int failed;
    struct serial_param_t ctl_param;
    short mystic;

    set_defaults( &ctl_param );
    get_arguments ( argc, argv, &ctl_param, &mystic);

    if( (failed = check_param( &ctl_param )) != 0 )
    {
        switch(failed)
        {
            case E_BAUDRATE:
                fprintf(stderr, "Invalid baudrate\n");
                break;
            case E_DATABIT:
                fprintf(stderr, "Invalid databits\n");
                break;
            case E_PARITY:
                fprintf(stderr, "Invalid parity\n");
                break;
            case E_STOPPBITS:
                fprintf(stderr, "Invalid stoppbits\n");
                break;
            case E_HANDSHAKE:
                fprintf(stderr, "Invalid handshake\n");
                break;
            case E_DEVICE:
                fprintf(stderr, "Invalid device\n");
                break;
            case E_NULL:
                fprintf(stderr, "cannot check parameter -> NULL\n");
                break;
        }
    }
    else
    {
        display = new smartTFT();
        if( (retVal = display->connect()) != E_OK )
        {
fprintf(stderr, "[%d]Connect failed\n", retVal );
        }
        else
        {
// sleep(1);
display->flushSerial();

            display->tft_fillScreen(ST7735_BLACK);

//            testdrawtext((char*) "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST7735_WHITE);

        // tft print function!
// !!!!!           tftPrintTest();

            // a single pixel
            display->tft_drawPixel(display->tft_width()/2, display->tft_height()/2, ST7735_GREEN);


            // line draw test
            testlines(ST7735_YELLOW);

            // optimized lines
            testfastlines(ST7735_RED, ST7735_BLUE);

            testdrawrects(ST7735_GREEN);

            testfillrects(ST7735_YELLOW, ST7735_MAGENTA);

            display->tft_fillScreen(ST7735_BLACK);

            testfillcircles(10, ST7735_BLUE);
            testdrawcircles(10, ST7735_WHITE);

            testroundrects();

            testtriangles();

            mediabuttons();

for(int i = 0; i < 20; i++ )
{

            display->tft_invertDisplay(true);
            sleep(2);
            display->tft_invertDisplay(false);
            sleep(2);
}
        }
    }

    return( retVal );
}


