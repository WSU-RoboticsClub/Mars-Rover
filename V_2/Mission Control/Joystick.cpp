#include "../Socket.h"

#define PORTNO 12345


// Custom Functions ***********************************************

bool handshake(Socket socket)
{
	
}

// Run Program ****************************************************

int main(void)
{
	Client_Socket socket(PORTNO);
	socket.open("localhost");
	
	while(1)
	{
		//Read from joystick and write values to the socket
	}
	
	return 0;
}