#pragma once

#define NETRETIFTRUE(statement, msg, ...)								\
if (statement)															\
{																		\
	printf("[ERROR][%s:%d][%d] " msg "\n",								\
			__FUNCTION__, __LINE__, WSAGetLastError(), ##__VA_ARGS__);	\
	return;									\
}

#define NETRETVALIFFALSE(statement, ret, msg, ...)						\
if (!(statement))														\
{																		\
	printf("[ERROR][%s:%d][%d] " msg "\n",								\
			__FUNCTION__, __LINE__, WSAGetLastError(), ##__VA_ARGS__);	\
	return ret;															\
}

#define NETEXITIFFALSE(statement, msg, ...)						\
if (!(statement))												\
{																\
	printf("[ERROR][%s:%d][%d] " msg "\n",						\
	__FUNCTION__, __LINE__, WSAGetLastError(), ##__VA_ARGS__);	\
	exit(1);													\
}