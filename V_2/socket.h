#ifndef SOCKET_H
#define SOCKET_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "core.h"

using namespace std;


// Base Socket Class ***************************************************************************************************

class Socket
{
public:
	
	// Public Methods
	virtual CODE_ERROR_T send(BYTE * const message, const int messageSize = 256) = 0;
	virtual CODE_ERROR_T receive(BYTE * const recieved, const int messageSize = 256) = 0;

protected:
	
	// Protected Members
	int m_sockfd, m_portno;
    struct sockaddr_in m_serv_addr;
};

// Client Socket Class *************************************************************************************************

class Client_Socket : public Socket
{

public:

	Client_Socket(const int new_portno = -1)
	{
		this->sockfd = -1;
		this->portno = new_portno;
		
		//Set complex data types to zero
		this->server = nullptr;
		bzero((char *)&(this->serv_addr), sizeof(this->serv_addr));
	}
	
	~Client_Socket()
	{
		this->disconnect();
	
		//Free pointers
		delete this->server;
	}

	// Public Methods
	CODE_ERROR_T connect(const char * const hostname);
	CODE_ERROR_T send(BYTE * const message, const int messageSize = 256);
	CODE_ERROR_T receive(BYTE * const recieved, const int messageSize = 255);

protected:

	// Protected Members
	struct hostent * m_server;
	
	//Protected Methods
	void disconnect();
};

// Server Socket Class *************************************************************************************************

class Server_Socket : public Socket
{	
public:

	Server_Socket(const int new_portno = -1)
	{
		this->sockfd = -1;
		this->newsockfd = -1;
		this->portno = new_portno;
		this->clilen = -1;
		
		//Set complex data types to zero
		bzero((char *)&(this->serv_addr), sizeof(this->serv_addr));
		bzero((char *)&(this->cli_addr), sizeof(this->cli_addr));
	}
	
	~Server_Socket()
	{
		char evacuated[256];
		bzero(evacuated, 256);
		
		//CLose the socket and pull information out
		this->disconnect(evacuated);
		
		//TODO: Log any evacuated data
	}

	// Public Methods
	CODE_ERROR_T connect();
	CODE_ERROR_T send(BYTE * const message, const int messageSize = 256);
	CODE_ERROR_T receive(BYTE * const recieved, const int messageSize = 255);

protected:
	
	// Protected Members
	int m_newsockfd;
	socklen_t m_clilen;
	
	struct sockaddr_in m_cli_addr;
	
	// Protected Methods
	void disconnect(BYTE * const evacuated);
};


#endif