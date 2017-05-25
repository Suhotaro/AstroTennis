#pragma once

#include <stdlib.h>
#include <stdio.h>

#define EXITIFFALSE(statement, msg, ...)											\
if (!statement)																		\
{																					\
	printf("[ERROR][%s:%d] " msg "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);		\
	exit(1);																		\
}

#define RETURNVALIFFALSE(statement, val, msg, ...)									\
if (!statement)																		\
{																					\
	printf("[ERROR][%s:%d] " msg "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);		\
	return val;																		\
}

#define RETURNIFFALSE(statement, msg, ...)											\
if (!statement)																		\
{																					\
	printf("[ERROR][%s:%d] " msg "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);		\
	return;																		\
}