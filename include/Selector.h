#pragma once

#include "Socket.h"

class RP_LIBS_API rpSelector
{
public:
	rpSelector() {}
	~rpSelector() {}

	virtual bool Init() = 0;
	virtual void Done() = 0;
	virtual bool Update() = 0;
	virtual int Errors() = 0;

protected:
	virtual void OnRead(char *__buffer, int __size) {}
	virtual void OnWrite(char *__buffer, int *__size) {}
	virtual void OnClose() {}
};
