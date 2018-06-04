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

int main( int argc, char *argv[] )
{
    int retVal = 0;

    display = new smartTFT();

//    display->tft_tft_println("lalala");
//    display->tft_tft_println(25);
//    display->tft_tft_println(25,HEX);
//    display->tft_tft_println();

//    display->tft_tft_print("lalala");
//    display->tft_tft_print(25);
//    display->tft_tft_print(25,HEX);

//    delete display;

  display->tft_fillScreen(ST7735_BLACK);



  // large block of text
  display->tft_fillScreen(ST7735_BLACK);

  testdrawtext((char*) "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST7735_WHITE);

  // tft print function!
  tftPrintTest();

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

  display->tft_invertDisplay(true);

  display->tft_invertDisplay(false);


    return( retVal );
}


#ifdef NEW_VERSION

/*
 ***********************************************************************
 *
 *  soehnle_drucker.c - simple program to get data from serial line on RPi
 *  			sent by a soehnle device
 *
 *  Copyright (C) 2013 Dreamshader (Dirk Schanz)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
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

/* **** soehnle_drucker.c **********************************************************
 * 
 * brief description:
 * listen on serial port for incoming data.
 * all received data will be formattet using printf and written to a logfile.
 * 
 * *********************************************************************************
 * Compile:
 *
 * gcc -o soehnle_drucker soehnle_drucker.c
 * 
 * *********************************************************************************
 * Options:
 *
 * -------------------- communication port for connection --------------------------
 *
 * --com devicename (same as --com=devicename resp. -c devicename)
 *
 *   Default is --com=/dev/ttyAMA0
 *
 * ---------------------- baudrate for serial connection ---------------------------
 *
 * --baud baudrate (same as --baud=baudrate resp. -b baudrate)
 *
 *   Default is --baud=9600
 *
 * ---------------------- databit for serial connection ----------------------------
 *
 * --data bits (same as --data=bits resp. -d bits)
 *			may be 5 up to 8
 *
 *   Default is --data=8
 *
 * ---------------------- parity for serial connection ----------------------------
 *
 * --parity parity (same as --parity=parity resp. -p parity)
 *			may be e/E (even), o/O (odd), n/N (none)
 *
 *   Default is --parity=n
 *
 * ---------------------- stoppbits for serial connection ----------------------------
 *
 * --stop stoppbits (same as --stop=stoppbits resp. -s stoppbits)
 *			may be 1 or 2
 *
 *   Default is --stop=1
 *
 * ---------------------- handshake for serial connection ----------------------------
 *
 * --handshake handshake (same as --handshake=handshake resp. -h handshake)
 *			may be n/N (no handshake), x/X (XON/XOFF)
 *
 *   Default is --handshake=n
 *
 * ---------------.------------------- help --.-------------------------------------
 *
 * --help 	(same as -? )
 *
 *   Show options and exit
 *
 * *********************************************************************************
*/


typedef struct serial_param_t {
unsigned char device[256];
int dev_fd;
struct termios oldtio;
struct termios rawtio;
unsigned int baud;
unsigned char databit;
unsigned char parity;
unsigned char stoppbits;
unsigned char handshake;
} serial_param;

int inp_present;

#define COMPORT			"/dev/ttyAMA0"
#define E_PARAM_BAUDRATE	-10
#define E_PARAM_DATABIT		-11
#define E_PARAM_PARITY		-12
#define E_PARAM_STOPPBITS	-13
#define E_PARAM_HANDSHAKE	-14
#define E_PARAM_DEVICE		-15
#define E_PARAM_NULL		-16
#define E_PARAM_NOFD		-17

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
		memset( ctl_param->device, '\0', sizeof(ctl_param->device) );
		strcpy( ctl_param->device, COMPORT );
		ctl_param->baud = 9600;
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
	fprintf(stderr, "Default is --com=/dev/ttyAMA0\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "--baud baudrate (same as --baud=baudrate resp. -b baudrate)\n");
	fprintf(stderr, "set speed to baudrate\n");
	fprintf(stderr, "Default is --baud=9600\n");
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
				if( strlen(optarg) < sizeof(ctl_param->device) )
				{
					strcpy( ctl_param->device, optarg );
				}
				else
				{
					help( ctl_param, E_PARAM_DEVICE);
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
 | typedef void (*sighandler_t)(int);
 |
 | Declaration for a signal handler
 -----------------------------------------------------------------------------------
*/

typedef void (*sighandler_t)(int);

/* ---------------------------------------------------------------------------------
 | static sighandler_t handle_signal (int sig_nr, sighandler_t signalhandler) 
 |
 | setup a new signal handling for a specific signal
 -----------------------------------------------------------------------------------
*/

static sighandler_t handle_signal (int sig_nr, sighandler_t signalhandler) 
{
   struct sigaction neu_sig, alt_sig;
   neu_sig.sa_handler = signalhandler;
   sigemptyset (&neu_sig.sa_mask);
   neu_sig.sa_flags = SA_RESTART;
   if (sigaction (sig_nr, &neu_sig, &alt_sig) < 0)
      return SIG_ERR;
   return alt_sig.sa_handler;
}

/* ---------------------------------------------------------------------------------
 | static void catch_SIGIO(int val)
 |
 | A simple handler that can be installed using handle_signal
 -----------------------------------------------------------------------------------
*/

static void catch_SIGIO(int val)
{
	inp_present = 1;
	return;
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
					fail = E_PARAM_BAUDRATE;
			}

			switch( ctl_param->databit )
			{
				case 5:
				case 6:
				case 7:
				case 8:
					break;
				default:
					fail = E_PARAM_DATABIT;
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
					fail = E_PARAM_PARITY;
			}

			switch( ctl_param->stoppbits )
			{
				case 1:
				case 2:
					break;
				default:
					fail = E_PARAM_STOPPBITS;
			}

			switch( ctl_param->handshake )
			{
				case 'n':
				case 'N':
				case 'x':
				case 'X':
					break;
				default:
					fail = E_PARAM_HANDSHAKE;
			}
		}
		else
		{
			fail = E_PARAM_DEVICE;
		}
	}
	else
	{
		fail = E_PARAM_NULL;
	}

	return( fail );
}


/* ---------------------------------------------------------------------------------
 | int open_device( struct serial_param_t *ctl_param )
 | 
 | open serial device
 -----------------------------------------------------------------------------------
*/

int open_device( struct serial_param_t *ctl_param )
{
	// open non-blocking

	if( ctl_param != NULL )
	{
		ctl_param->dev_fd = open( ctl_param->device, O_RDWR|O_NOCTTY|O_NONBLOCK);
		return( ctl_param->dev_fd );
	}

	return( E_PARAM_NULL );
}

/* ---------------------------------------------------------------------------------
 | void close_device( struct serial_param_t *ctl_param )
 | 
 | close the serial device
 -----------------------------------------------------------------------------------
*/

void close_device( struct serial_param_t *ctl_param )
{
	if( ctl_param != NULL )
	{
		if( ctl_param->dev_fd > 0 )
		{
			close( ctl_param->dev_fd );
			ctl_param->dev_fd = 0;
		}
	}
}

/* ---------------------------------------------------------------------------------
 | int reset_device( struct serial_param_t *ctl_param )
 | 
 | reset old parameter of serial port
 -----------------------------------------------------------------------------------
*/

int reset_device( struct serial_param_t *ctl_param )
{
	int fail;

	if( ctl_param != NULL )
	{
        	fail = tcsetattr( ctl_param->dev_fd, TCSANOW, &ctl_param->oldtio );
	}
	else
	{
		fail = E_PARAM_NULL;
	}

	return(fail);
}

/* ---------------------------------------------------------------------------------
 | int setup_device( struct serial_param_t *ctl_param )
 | 
 | set parameter for serial communication, save current settings
 -----------------------------------------------------------------------------------
*/

int setup_device( struct serial_param_t *ctl_param )
{
	int fail = 0;

	if( ctl_param != NULL )
	{
        	if( ctl_param->dev_fd > 0 )
		{
        		fail = tcgetattr( ctl_param->dev_fd, &ctl_param->oldtio );
        		fail = tcgetattr( ctl_param->dev_fd, &ctl_param->rawtio );
			cfmakeraw( &ctl_param->rawtio );

			switch( ctl_param->baud )
			{
				case     50:
					cfsetspeed ( &ctl_param->rawtio, B50 );
					break;
				case     75:
					cfsetspeed ( &ctl_param->rawtio, B75 );
					break;
				case    110:
					cfsetspeed ( &ctl_param->rawtio, B110 );
					break;
				case    134:
					cfsetspeed ( &ctl_param->rawtio, B134 );
					break;
				case    150:
					cfsetspeed ( &ctl_param->rawtio, B150 );
					break;
				case    200:
					cfsetspeed ( &ctl_param->rawtio, B200 );
					break;
				case    300:
					cfsetspeed ( &ctl_param->rawtio, B300 );
					break;
				case    600:
					cfsetspeed ( &ctl_param->rawtio, B600 );
					break;
				case   1200:
					cfsetspeed ( &ctl_param->rawtio, B1200 );
					break;
				case   1800:
					cfsetspeed ( &ctl_param->rawtio, B1800 );
					break;
				case   2400:
					cfsetspeed ( &ctl_param->rawtio, B2400 );
					break;
				case   4800:
					cfsetspeed ( &ctl_param->rawtio, B4800 );
					break;
				case   9600:
					cfsetspeed ( &ctl_param->rawtio, B9600 );
					break;
				case  19200:
					cfsetspeed ( &ctl_param->rawtio, B19200 );
					break;
				case  38400:
					cfsetspeed ( &ctl_param->rawtio, B38400 );
					break;
				case  57600:
					cfsetspeed ( &ctl_param->rawtio, B57600 );
					break;
				case 115200:
					cfsetspeed ( &ctl_param->rawtio, B115200 );
					break;
				case 230400:
					cfsetspeed ( &ctl_param->rawtio, B230400 );
					break;
				case 460800:
					cfsetspeed ( &ctl_param->rawtio, B460800 );
					break;
				default:
					fail = E_PARAM_BAUDRATE;
			}
	
			switch( ctl_param->databit )
			{
				case 5:
					ctl_param->rawtio.c_cflag |= CS5;
					break;
				case 6:
					ctl_param->rawtio.c_cflag |= CS6;
					break;
				case 7:
					ctl_param->rawtio.c_cflag |= CS7;
					break;
				case 8:
					ctl_param->rawtio.c_cflag |= CS8;
					break;
				default:
					fail = E_PARAM_DATABIT;
			}
	
			switch( ctl_param->parity )
			{
				case 'o':
				case 'O':
					ctl_param->rawtio.c_cflag |= PARODD | PARENB;
					break;
				case 'e':
				case 'E':
					ctl_param->rawtio.c_cflag |= PARENB;
					break;
				case 'n':
				case 'N':
					ctl_param->rawtio.c_cflag |= IGNPAR;
					ctl_param->rawtio.c_cflag &= ~PARENB;
					break;
				default:
					fail = E_PARAM_PARITY;
			}
	
			switch( ctl_param->stoppbits )
			{
				case 1:
					break;
				case 2:
					ctl_param->rawtio.c_cflag |= CSTOPB;
					break;
				default:
					fail = E_PARAM_STOPPBITS;
			}
	
			switch( ctl_param->handshake )
			{
				case 'n':
				case 'N':
					ctl_param->rawtio.c_cflag |= CLOCAL;
					break;
				case 'x':
				case 'X':
					ctl_param->rawtio.c_iflag |= IXON;
					break;
				default:
					fail = E_PARAM_HANDSHAKE;
			}
		}
		else
		{
			fail = E_PARAM_NOFD;
		}
	}
	else
	{
		fail = E_PARAM_NULL;
	}

	if( !fail )
	{
        	tcflush( ctl_param->dev_fd, TCIFLUSH);
        	fail = tcsetattr( ctl_param->dev_fd, TCSANOW, &ctl_param->rawtio );
	}
	
	return( fail );
}


/* ---------------------------------------------------------------------------------
 | int process_data( struct serial_param_t *ctl_param )
 | 
 | print data to stdout
 | return 1 -> continue loop, return 0 -> leave loop
 -----------------------------------------------------------------------------------
*/

int process_data( struct serial_param_t *ctl_param )
{
	unsigned char data[512];
	int res;

	memset( data, '\0', sizeof(data) );

	res = read(ctl_param->dev_fd, data, sizeof(data));
	
	printf("%s\n", data);
	return(1);
}


main( int argc, char **argv )
{

	struct serial_param_t ctl_param;
	short mystic;
	int failed;
	int res;
	struct timeval timeout;
	int loop;


	timeout.tv_usec = 0;  /* milliseconds */
	timeout.tv_sec  = 1;  /* seconds */

	set_defaults( &ctl_param );
	get_arguments ( argc, argv, &ctl_param, &mystic);

	if( (failed = check_param( &ctl_param )) == 0 )
	{
		if( (failed = open_device( &ctl_param )) > 0 )
		{
			if( (failed = setup_device( &ctl_param )) == 0 )
			{
				loop = 1;
				inp_present = 0;
				handle_signal( SIGIO, catch_SIGIO );
				fcntl(ctl_param.dev_fd, F_SETOWN, getpid());
				fcntl(ctl_param.dev_fd, F_SETFL, FASYNC);

				while (loop) 
				{
					if( inp_present )
					{
						loop = process_data( &ctl_param );
						inp_present = 0;
					}
					usleep(100000);
				}
				reset_device( &ctl_param );
			}
			else
			{
				perror("failed to setup device");
			}
			close_device( &ctl_param );
		}
		else
		{
			perror("failed to open device");
		}
	}
	else
	{
		switch(failed)
		{
			case E_PARAM_BAUDRATE:
				fprintf(stderr, "Invalid baudrate\n");
				break;
			case E_PARAM_DATABIT:
				fprintf(stderr, "Invalid databits\n");
				break;
			case E_PARAM_PARITY:
				fprintf(stderr, "Invalid parity\n");
				break;
			case E_PARAM_STOPPBITS:
				fprintf(stderr, "Invalid stoppbits\n");
				break;
			case E_PARAM_HANDSHAKE:
				fprintf(stderr, "Invalid handshake\n");
				break;
			case E_PARAM_DEVICE:
				fprintf(stderr, "Invalid device\n");
				break;
			case E_PARAM_NULL:
				fprintf(stderr, "cannot check parameter -> NULL\n");
				break;
			case E_PARAM_NOFD:
				fprintf(stderr, "Invalid filedescriptor\n");
				break;
		}

	}

}



#endif // NEW_VERSION


