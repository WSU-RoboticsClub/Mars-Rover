#ifndef CORE_H
#define CORE_H


// Generic Types -------------------------------------------------------------------------------------------------------

typedef 	unsigned char 	BYTE;
typedef 	unsigned short 	WORD;
typedef		unsigned long	DWORD;

// Enumerated types ----------------------------------------------------------------------------------------------------

typedef enum
{
	//Addresses for the I2C-connected microcontroller network
	//7-bit values. Cannot go above a value of 127
	//Addresses 0x00 - 0x07 are reserved
	
	//Central Computing Unit
	ADDRESS_CCU_01 = 0x08,
	
	//Drive-Train Unit
	ADDRESS_DTU_01 = 0x1A,
	ADDRESS_DTU_02 = 0x1B,
	ADDRESS_DTU_03 = 0x1C,
	ADDRESS_DTU_04 = 0x1D,
	
	//Power Supply Unit
	ADDRESS_PSU_01 = 0x2A,
	
	ADDRESS_MAX = 0x7F
	
} ADDRESS_T;

//Enumerated type for error codes
typedef enum
{
	ERR_NONE				=	0x00
	
	//Socket related errors
	ERR_SOCK_NOHOST			=	0x01,	//Hostname not found
	ERR_SOCK_OPEN			=	0x02,	//Error opening socket
	ERR_SOCK_CONNECT		=	0x03,	//Error connecting to socket
	ERR_SOCK_BIND			=	0x04,
	ERR_SOCK_WRITE			=	0x05,	//Error writing to socket
	ERR_SOCK_READ			=	0x06,	//Error reading from socket
	
	
	ERR_GENERIC				=	0x0E,	//Generic "error occured" code
	
	MAX_ERR_VAL				=	0x0F
} CODE_ERROR_T;


#endif