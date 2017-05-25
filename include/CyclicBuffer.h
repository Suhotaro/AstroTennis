#pragma once

#include "stdafx.h"
#include <string>

class CyclicBuffer
{
public:
	CyclicBuffer();
	~CyclicBuffer();

	void Add(char *buffer, int size);
	void Pop(char *buffer, int*size, int maxBufferSize);

	const HANDLE& Signal();
private:
	HANDLE __signal;
	std::string __buffer;
};