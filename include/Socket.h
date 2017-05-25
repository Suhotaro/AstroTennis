#pragma once

#include "rp_libs.h"
#include <winsock2.h>

class RP_LIBS_API rpSocketBase
{
protected:
	int __af;
	int __type;
	int __protocol;
	SOCKET __socket;
public:
	rpSocketBase(int af, int type, int protocol);
	rpSocketBase(SOCKET socket);
	~rpSocketBase();

	SOCKET& Handle();
};

class RP_LIBS_API rpSocket : public rpSocketBase
{
	using rpParrent = rpSocketBase;

public:
	rpSocket(int af, int type, int protocol);
	rpSocket(SOCKET socket);
	~rpSocket() {}

	int Write(const char *buf, size_t len, int flags = 0);
	int Read(char *buf, size_t len, int flags);

	virtual bool Init();
};
