#include "stdafx.h"

#include <winsock2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

#include "LibInit.h"
#include "SocketTCP.h"
#include "client.h"
#include "ThreadPool.h"

#define DEFAULT_COUNT	20
#define DEFAULT_PORT	5150
#define DEFAULT_BUFFER	4096
#define DEFAULT_MESSAGE	"Quick brown fox jumps over the lazy dog"

char szServer[128], szMessage[1024];
int	iPort = DEFAULT_PORT;
DWORD dwCount = DEFAULT_COUNT;

int main(int argc, char** argv)
{
	/*
	WSADATA wsd;
	char szBuffer[DEFAULT_BUFFER];
	int ret;




	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("ERROR: WSAStartup failed %d\n", WSAGetLastError());
		return 1;
	}

	strcpy_s(szMessage, DEFAULT_MESSAGE);

	rpTCPClientSocket s("127.0.0.1", DEFAULT_PORT);
	ret = s.Init();
	if (!ret)
		return 1;

	for (int i = 0; i < dwCount; i++)
	{
		ret = s.Write(szMessage, strlen(szMessage), 0);
		if (ret == 0) //Server has been correctly disconnected
			break;
		else if (ret == SOCKET_ERROR)
		{
			printf("ERROR: send failed : %d\n", WSAGetLastError());
			return 1;
		}
 
		printf("Send %d bytes\n", ret);

		ret = s.Read(szBuffer, DEFAULT_BUFFER, 0);
		if (ret == 0) //Server has been correctly disconnected
			break;
		else if (ret == SOCKET_ERROR)
		{
			printf("ERROR: recv failed : %d\n", WSAGetLastError());
			return 1; 
		}

		szBuffer[ret - 1] = '\0';

		Msg m;
		m.unserialize(szBuffer);

		printf("INFO: received[%d bytes] msg: %s\n", ret, szBuffer);
	}


	WSACleanup();

	*/

	rpLibInit();

	std::shared_ptr<ThreadPool> pool(new ThreadPool);
	eClient client(std::string("client"), pool);

	client.Init();
	client.Start();
	client.Send("Hello");

	std::this_thread::sleep_for(std::chrono::seconds(360));

	client.Done();
	rpLibDone();



	return 0;
}

