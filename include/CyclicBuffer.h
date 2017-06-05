#pragma once

#include "rp_libs.h"
#include "stdafx.h"
#include <string>

class RP_LIBS_API CyclicBuffer
{
public:
	CyclicBuffer();
	~CyclicBuffer();

	void Add(char *buffer, int size);
	void Pop(char *buffer, int*size, int maxBufferSize);

	std::string Read();
	void Write(std::string str);

	const HANDLE& Signal();
private:
	HANDLE __signal;
	std::string __buffer;
};