#pragma once

#include "Socket.h"
#include "Selector.h"

#include <vector>
#include <string>

class CyclicBuffer;

class rpSelectorClient : public rpSelector
{
	typedef rpSelector eInherited;
public:
	rpSelectorClient(std::string address, int port, CyclicBuffer *inBuf, CyclicBuffer *outBuf, int flags);
	~rpSelectorClient();

	virtual bool Init() override;
	virtual void Done() override;
	virtual bool Update() override;
	virtual int Errors() override;

protected:
	virtual void OnRead(char *buffer, int size) override;
	virtual void OnWrite(char *buffer, int *size) override;
	virtual void OnClose() override;

	//Correct return value has to be returned to left Update properly
	bool processEventSocket(WSAEVENT event);
	bool processEventDone(WSAEVENT event);
	bool processEventDataToWrite(WSAEVENT event);

	std::string __address;
	int __port;
	rpSocket *__socket;

	HANDLE __signalSocket;
	HANDLE __signalDone;

	CyclicBuffer *__inBuf;
	CyclicBuffer *__outBuf;

	std::vector<SOCKET> sockets;
	std::vector<WSAEVENT> events;

	char *__buffer;
	int __size;

	int __ret;
	int __flags;
};
