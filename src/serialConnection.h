/*
 ***********************************************************************
 *
 *  serialConnection.h - a class for simplifying access to a
 *                       serial line
 *
 *  Copyright (C) 2018 Dreamshader (Dirk Schanz)
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

#ifndef _SERIAL_CONNECTION_H_
#define _SERIAL_CONNECTION_H_

#include <iostream>
#include <string>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/param.h>
#include <fcntl.h>
#include <termios.h>


#ifdef __cplusplus
extern "C" {
#endif
 
using namespace std;

#define DEFAULT_CONNECTIONTYPE -1
#define DEFAULT_DEVICE           "/dev/ttyUSB0"
#define DEFAULT_BAUD             38400
#define DEFAULT_DATABIT          8
#define DEFAULT_STOPBITS         1
#define DEFAULT_PARITY           'N'
#define DEFAULT_HANDSHAKE        'N'

#define E_OK                       0
#define E_FAIL                    -1

#define E_PARAM_BAUDRATE         -10
#define E_PARAM_DATABIT	         -11
#define E_PARAM_PARITY	         -12
#define E_PARAM_STOPBITS         -13
#define E_PARAM_HANDSHAKE        -14
#define E_PARAM_DEVICE           -15
#define E_PARAM_NULL             -16
#define E_PARAM_NOFD             -17
#define E_PARAM_LENGTH           -18
#define E_NULL_CONNECTION        -19

#define CONNECTION_TYPE_UART      'u'
#define CONNECTION_TYPE_I2C       'i'
#define CONNECTION_TYPE_SPI       's'

#define CONNTYPE_SET            1

#define INATERFACE_SET          2
#define SPEED_SET               4
#define PARITY_SET              8
#define DATABITS_SET           16
#define STOPBITS_SET           32
#define UART_PARAM_COMPLETE    63

#define I2CSDA_SET              2
#define I2CSCL_SET              4
#define I2CADDR_SET             8
#define I2C_PARAM_COMPLETE     15

#define SPIMOSI_SET             2
#define SPIMISO_SET             4
#define SPISCLK_SET             8
#define SPICS_SET              16
#define SPI_PARAM_COMPLETE     31



// #define SEND_BUFFER_SIZE    1024

class serialConnection {

    private:
        int16_t        dev_fd;
        struct termios newtio;
        bool           dataReceived;
        int8_t         connType;
        uint32_t       connFlags;

        char           *device;
        uint32_t       baud;
        int16_t        databits;
        int8_t         parity;
        int16_t        stopbits;
        int8_t         handshake;

//     uint8_t _sendBuffer[SEND_BUFFER_SIZE];

    public:
        int            errorNum;

        serialConnection( char *devname = (char*) DEFAULT_DEVICE, 
                          uint32_t baud = DEFAULT_BAUD, 
                          int16_t databits = DEFAULT_DATABIT, 
                          int8_t parity = DEFAULT_PARITY, 
                          int16_t stopbits = DEFAULT_STOPBITS, 
                          int8_t handshake = DEFAULT_HANDSHAKE )
        {

            if( isValidDevice( devname ) )
            {
                this->device = strdup(devname);
                if( isValidBaud( baud ) )
                {
                    this->baud = baud;
                    if( isValidDatabits( databits ) )
                    {
                        this->databits = databits;
                        if( isValidParity( parity ) )
                        {
                            this->parity = parity;
                            if( isValidStopbits( stopbits ) )
                            {
                                this->stopbits = stopbits;
                                if( isValidHandshake( handshake ) )
                                {
                                    this->handshake = handshake;
                                }
                            }
                        }
                    }
                }
            }
        }


        bool isValidBaud( uint32_t baud );
        bool isValidDatabits( int16_t databits );
        bool isValidParity( int8_t parity );
        bool isValidStopbits( int16_t stopbits );
        bool isValidHandshake( int8_t handshake );
        bool isValidDevice( char* pDeviceName );

        int set_termios( void );

        int setup( char *devname, uint32_t baud, int16_t databits,
                   int8_t parity, int16_t stopbits, int8_t handshake );

        int ser_open( char *devname, uint32_t baud, short databits, 
                  int8_t parity, int16_t stopbits, int8_t handshake );

        int ser_open( void );

        int ser_close( void );
        int ser_read( char* pBuffer, int bufLen );
        int ser_write( char* pBuffer, int wrLen );


};

#ifdef __cplusplus
}
#endif


#endif // _SERIAL_CONNECTION_H_
