#pragma once

#include "rp_libs.h"
#include "Socket.h"

#include <winsock2.h>
#include <string>

class RP_LIBS_API rpTCPServerSocket : public rpSocket
{
	using rpParrent = rpSocket;
public:
	rpTCPServerSocket(SOCKET socket);
	~rpTCPServerSocket() {}
};

class RP_LIBS_API rpTCPClientSocket : public rpSocket
{
	using rpParrent = rpSocket;
protected:
	std::string __address;
	int __port;
public:
	rpTCPClientSocket(std::string address, int port,
		int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_IP);

	~rpTCPClientSocket() {}

	virtual bool Init();
};