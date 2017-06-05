#include "stdafx.h"

#include <WinSock2.h>

#include "SocketTCP.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#define DEFAULT_PORT	5150
#define DEFAULT_BUFFER	4096

int iPort = DEFAULT_PORT;
BOOL bInterface = FALSE, bRecvOnly = FALSE;
char szAddress[126];

void usage()
{
	printf("usage: server [-p:x] [-i:IP] [-o]\n");
	printf("	-p:x	Port number to lisetn on\n");
	printf("	-i:str	Interface to lisetn on\n");
	printf("	-o		Do not echo the data back\n\n");

	ExitProcess(1);
}
		
void ValidateArgs(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		if ((argv[i][0] == '-' || argv[i][0] == '/'))
		{
			switch (tolower(argv[i][0]))
			{
			case 'p':
				iPort = atoi(&argv[i][3]);
				break;
			case 'i':
				if (strlen(argv[i]) > 3)
					strcpy_s(szAddress, &argv[i][3]);
				break;
			case 'o':
				bRecvOnly = true;
				break;
			default:
				usage();
				break;
			}
		}
	}
}

class Msg
{
	int __x;
	int __y;
public:
	Msg(int x, int y)
		: __x(x), __y(y)
	{}

	~Msg() {}

	int X() { return __x; }
	int Y() { return __y; }

	void inc()
	{
		__x++;
		__y++;
	}

	std::string serialize()
	{
		std::stringstream res;
		res << "+";
		res << __x;
		res << ":";
		res << __y;
		res << "+";

		return res.str();
	}

	void unserialize(std::string str)
	{
		sscanf_s(str.c_str(), "+%d:%d+", &__x, &__y);
	}
};

DWORD WINAPI ClientThread(LPVOID lpParam)
{
	rpTCPServerSocket sock((SOCKET)lpParam);
	char szBuff[DEFAULT_BUFFER];
	int ret, nLeft, idx;

	while (true)
	{
		
		ret = sock.Read(szBuff, DEFAULT_BUFFER, 0);
		if (ret == 0) //Correct disconnection
			break;
		else if (ret == SOCKET_ERROR)
		{
			printf("ERROR: recv failed: %d\n", WSAGetLastError());
			break;
		}

		szBuff[ret] = '\0';
		printf("RECV: %s\n", szBuff);

		ret = sock.Write(szBuff, ret);
		if (ret = 0)
			break;
		else if (ret == SOCKET_ERROR)
		{
			printf("ERROR: send failed: %d\n", WSAGetLastError());
			break;
		}
	}

	return 0;
}



//todo do not use deprecated API
int main(int argc, char **argv)
{
	WSADATA wsd;
	SOCKET sListen, sClient;
	int iAddrSize;
	HANDLE hThread;
	DWORD dwThreadId;
	struct sockaddr_in local, client;
	
	ValidateArgs(argc, argv);

	printf("Started");

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("ERROR: WSAStartup failed\n");
		return 1;
	}

	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sListen == SOCKET_ERROR)
	{
		printf("ERROR: create listen socket failed %d\n", WSAGetLastError());
		return 1;
	}

	if (bInterface)
	{
		local.sin_addr.S_un.S_addr = inet_addr(szAddress);
		if (local.sin_addr.S_un.S_addr == INADDR_NONE)
			usage();
	}
	else
		local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_family = AF_INET;
	local.sin_port = htons(iPort);

	if (bind(sListen, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
	{
		printf("ERROR: create listen socket failed %d\n",
			WSAGetLastError());
		return 1;
	}

	listen(sListen, 0);

	while (true)
	{
		iAddrSize = sizeof(client);

		sClient = accept(sListen, (struct sockaddr*)&client, &iAddrSize);
		if (sClient == INVALID_SOCKET)
		{
			printf("ERROR: create accept failed %d\n", WSAGetLastError());
			return 1;
		}

		printf("INFO: accepted client: %s:%d\n",
			inet_ntoa(client.sin_addr),
			ntohd(client.sin_port));

		hThread = CreateThread(NULL, 0, ClientThread, (LPVOID)sClient, 0, &dwThreadId);
		if (!hThread)
		{
			printf("ERROR: CreateThread failed %d\n",
				GetLastError());
			return 1;
		}
		CloseHandle(hThread);
	}

	closesocket(sListen);

	WSACleanup();
    return 0;
}

