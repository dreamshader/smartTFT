/*
 ***********************************************************************
 *
 *  serialConnection.cpp - a class for simplifying access to a
 *                         serial line
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

#include "serialConnection.h"

/* ----------------------------------------------------------------------------
 * bool isValidDevice( char* pDeviceName )
 *
 * Check device for presence and accessibilty
 * return true on succes, false otherwise
 ------------------------------------------------------------------------------
*/
bool serialConnection::isValidDevice( char* pDeviceName )
{
    bool retVal = false;

    if( pDeviceName != NULL )
    {
        if( access( pDeviceName, F_OK) == 0)
        {
            retVal = true;
            errorNum = E_OK;
        }
        else
        {
            errorNum = E_PARAM_DEVICE;
        }
    }
    else
    {
        errorNum = E_PARAM_NULL;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * bool isValidBaud( unsigned int baud )
 *
 * Check whether baudrate is valid
 * return true on succes, false otherwise
 ------------------------------------------------------------------------------
*/
bool serialConnection::isValidBaud( uint32_t baud )
{
    bool retVal = false;

    switch( baud )
    {
        case     50:
        case     75:
        case    110:
        case    134:
        case    150:
        case    200:
        case    300:
        case    600:
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
            retVal = true;
            errorNum = E_OK;
            break;
        default:
            errorNum = E_PARAM_BAUDRATE;
            break;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * bool isValidDatabits( short databits )
 *
 * Check whether databits are valid
 * return true on succes, false otherwise
 ------------------------------------------------------------------------------
*/
bool serialConnection::isValidDatabits( int16_t databits )
{
    bool retVal = false;

    switch( databits )
    {
        case 5:
        case 6:
        case 7:
        case 8:
            retVal = true;
            errorNum = E_OK;
            break;
        default:
            errorNum = E_PARAM_DATABIT;
            break;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * bool isValidParity( char parity )
 *
 * Check whether parity is valid
 * return true on succes, false otherwise
 ------------------------------------------------------------------------------
*/
bool serialConnection::isValidParity( int8_t parity )
{
    bool retVal = false;

    switch( parity )
    {
        case 'o':
        case 'O':
        case 'e':
        case 'E':
        case 'n':
        case 'N':
            retVal = true;
            errorNum = E_OK;
            break;
        default:
            errorNum = E_PARAM_PARITY;
            break;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * bool isValidStopbits( short stopbits )
 *
 * Check whether stopbits are valid
 * return true on succes, false otherwise
 ------------------------------------------------------------------------------
*/
bool serialConnection::isValidStopbits( int16_t stopbits )
{
    bool retVal = false;

    switch( stopbits )
    {
        case 1:
        case 2:
            retVal = true;
            errorNum = E_OK;
            break;
        default:
            errorNum = E_PARAM_STOPBITS;
            break;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * bool isValidHandshake( char handshake )
 *
 * Check whether handshake is valid
 * return true on succes, false otherwise
 ------------------------------------------------------------------------------
*/
bool serialConnection::isValidHandshake( int8_t handshake )
{
    bool retVal = false;

    switch( handshake )
    {
        case 'n':
        case 'N':
        case 'x':
        case 'X':
            retVal = true;
            errorNum = E_OK;
            break;
        default:
            errorNum = E_PARAM_HANDSHAKE;
            break;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int setup( char *devname, unsigned int baud, short databits,
 *            char parity, short stopbits, char handshake )
 *
 * set all connection parameters at once
 * returns E_OK on succes, otherwise an error number
 ------------------------------------------------------------------------------
*/
int serialConnection::setup( char *devname, uint32_t baud, int16_t databits,
                         int8_t parity, int16_t stopbits, int8_t handshake )
{
    if( isValidDevice( devname ) )
    {
        if( this->device != NULL )
        {
            free( this->device );
        }
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

    return( errorNum );
}

/* ----------------------------------------------------------------------------
 * int serialConnection::set_termios( void )
 *
 * set parameter for current connection
 * returns E_OK on succes, otherwise an error number
 ------------------------------------------------------------------------------
*/
int serialConnection::set_termios( void )
{
    int retVal;
    this->errorNum = E_OK;

    if( this->dev_fd > 0 )
    {
        switch( this->baud )
        {
            case     50:
                cfsetspeed ( &this->newtio, B50 );
                break;
            case     75:
                cfsetspeed ( &this->newtio, B75 );
                break;
            case    110:
                cfsetspeed ( &this->newtio, B110 );
                break;
            case    134:
                cfsetspeed ( &this->newtio, B134 );
                break;
            case    150:
                cfsetspeed ( &this->newtio, B150 );
                break;
            case    200:
                cfsetspeed ( &this->newtio, B200 );
                break;
            case    300:
                cfsetspeed ( &this->newtio, B300 );
                break;
            case    600:
                cfsetspeed ( &this->newtio, B600 );
                break;
            case   1200:
                cfsetspeed ( &this->newtio, B1200 );
                break;
            case   1800:
                cfsetspeed ( &this->newtio, B1800 );
                break;
            case   2400:
                cfsetspeed ( &this->newtio, B2400 );
                break;
            case   4800:
                cfsetspeed ( &this->newtio, B4800 );
                break;
            case   9600:
                cfsetspeed ( &this->newtio, B9600 );
                break;
            case  19200:
                cfsetspeed ( &this->newtio, B19200 );
                break;
            case  38400:
                cfsetspeed ( &this->newtio, B38400 );
                break;
            case  57600:
                cfsetspeed ( &this->newtio, B57600 );
                break;
            case 115200:
                cfsetspeed ( &this->newtio, B115200 );
                break;
            case 230400:
                cfsetspeed ( &this->newtio, B230400 );
                break;
            case 460800:
                cfsetspeed ( &this->newtio, B460800 );
                break;
            default:
                errorNum = E_PARAM_BAUDRATE;
                break;
        }

        switch( this->databits )
        {
            case 5:
                this->newtio.c_cflag |= CS5;
                break;
            case 6:
                this->newtio.c_cflag |= CS6;
                break;
            case 7:
                this->newtio.c_cflag |= CS7;
                break;
            case 8:
                this->newtio.c_cflag |= CS8;
                break;
            default:
                errorNum = E_PARAM_DATABIT;
                break;
        }

        switch( this->parity )
        {
            case 'o':
            case 'O':
                this->newtio.c_cflag |= PARODD | PARENB;
                break;
            case 'e':
            case 'E':
                this->newtio.c_cflag |= PARENB;
                break;
            case 'n':
            case 'N':
                this->newtio.c_cflag |= IGNPAR;
                this->newtio.c_cflag &= ~PARENB;
                break;
            default:
                errorNum = E_PARAM_PARITY;
                break;
        }

        switch( this->stopbits )
        {
            case 1:
                break;
            case 2:
                this->newtio.c_cflag |= CSTOPB;
                break;
            default:
                errorNum = E_PARAM_STOPBITS;
                break;
        }

        switch( this->handshake )
        {
            case 'n':
            case 'N':
                this->newtio.c_cflag |= CLOCAL;
                break;
            case 'x':
            case 'X':
                this->newtio.c_iflag |= IXON;
                break;
            default:
                errorNum = E_PARAM_HANDSHAKE;
                break;
        }
    }

    if( this->errorNum == E_OK )
    {
        tcflush( this->dev_fd, TCIFLUSH);
        if( (retVal = tcsetattr( this->dev_fd, TCSANOW, &this->newtio )) == 0 )
        {
            retVal = tcsetattr( this->dev_fd, TCSANOW, &this->newtio );
        }
        this->errorNum = errno;
    }
	
    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int ser_open( char *devname, unsigned int baud, short databits,
 *               char parity, short stopbits, char handshake )
 *
 * open connection with given parameters
 * returns E_OK on succes, otherwise an error number
 ------------------------------------------------------------------------------
*/
int serialConnection::ser_open( char *devname, uint32_t baud, 
                                int16_t databits, int8_t parity, 
                                int16_t stopbits, int8_t handshake )
{
    int retVal = E_OK;

    if( (retVal = setup( devname, baud, databits, parity, 
                        stopbits, handshake )) == E_OK )
    {
	if( (this->dev_fd = open( device, O_RDWR|O_NOCTTY|O_NONBLOCK)) <= 0 )
        {
            this->errorNum = errno;
            retVal = E_FAIL;
        }
        else
        {
            tcgetattr( this->dev_fd, &this->newtio );
            cfmakeraw( &this->newtio );
            retVal = set_termios( );
        }
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int ser_open( char *devname, unsigned int baud, short databits,
 *               char parity, short stopbits, char handshake )
 *
 * open connection with given parameters
 * returns E_OK on succes, otherwise an error number
 ------------------------------------------------------------------------------
*/
int serialConnection::ser_open( void )
{
    int retVal = E_OK;

    if( (this->dev_fd = open( device, O_RDWR|O_NOCTTY|O_NONBLOCK)) <= 0 )
    {
        this->errorNum = errno;
        retVal = E_FAIL;
    }
    else
    {
        tcgetattr( this->dev_fd, &this->newtio );
        cfmakeraw( &this->newtio );
        retVal = set_termios( );
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int ser_close( void )
 *
 * close current connection
 * returns E_OK on succes, otherwise an error number
 ------------------------------------------------------------------------------
*/
int serialConnection::ser_close( void )
{
    int retVal = E_OK;

    if( this->dev_fd > 0 )
    {
        close( this->dev_fd );
        this->dev_fd = 0;
    }
    else
    {
        retVal = E_PARAM_NOFD;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int ser_read( char* pBuffer, int bufLen )
 *
 * try to read from current connection
 * read up to bufLen bytes into location where pBuffer points to.
 * returns amount of bytes read on succes, otherwise an error number
 ------------------------------------------------------------------------------
*/
int serialConnection::ser_read( char* pBuffer, int bufLen )
{
    int retVal = E_OK;

    if( pBuffer != NULL )
    {
        if( this->dev_fd > 0 )
        {
            if( bufLen >= 0 )
            {
                if( bufLen > 0 )
                {
                    char c = 0;
                    int idx = 0;
                    int endOfData = 0;
                    int failtries;
#define MAX_FAIL_TRIES   10

                    while( !endOfData )
                    {
                        if( (retVal = read( this->dev_fd, &c, 1 )) > 0 )
                        {
                            failtries = 0;
                            if( c == '\n' )
                            {
                                endOfData = 1;
                            }
                            else
                            {
                                pBuffer[idx++] = c;
                                pBuffer[idx] = '\0';
                            }
                        }
                        else
                        {
                            usleep(100000);
                            if( ++failtries >= MAX_FAIL_TRIES )
                            {
                                break;
                            }

                        }
                    }

//                    retVal = read( this->dev_fd, pBuffer, bufLen );
                    this->errorNum = errno;
                }
            }
            else
            {
                retVal = E_PARAM_LENGTH;
            }
        }
        else
        {
            retVal = E_PARAM_NOFD;
        }
    }
    else
    {
        retVal = E_PARAM_NULL;
    }

    return( retVal );
}

/* ----------------------------------------------------------------------------
 * int ser_write( char* pBuffer, int bufLen )
 *
 * try to write to current connection
 * write bufLen bytes from pBuffer to current connection.
 * returns amount of bytes written on succes, otherwise an error number
 ------------------------------------------------------------------------------
*/
int serialConnection::ser_write( char* pBuffer, int wrLen )
{
    int retVal = E_OK;

    if( pBuffer != NULL )
    {
        if( this->dev_fd > 0 )
        {
            if( wrLen >= 0 )
            {
                if( wrLen > 0 )
                {
                    retVal = write( this->dev_fd, pBuffer, wrLen );
                    this->errorNum = errno;
                }
            }
            else
            {
                retVal = E_PARAM_LENGTH;
            }
        }
        else
        {
            retVal = E_PARAM_NOFD;
        }
    }
    else
    {
        retVal = E_PARAM_NULL;
    }

    return( retVal );
}

