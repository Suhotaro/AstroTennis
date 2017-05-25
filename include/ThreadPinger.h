#pragma once

#include <string>
#include <thread>

#include "ThreadRunner.h"
#include "ThreadPool.h"

class Pinger : public ThreadRunner
{
	using Inherited = ThreadRunner;
public:
	Pinger(std::string threadName, std::shared_ptr<ThreadPool> pool) :
		Inherited(threadName, pool)
	{}

	virtual void Task();

private:
};