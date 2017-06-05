#pragma once

#include "ThreadRunner.h"
#include "ThreadPool.h"
#include "SelectorClient.h"
#include "CyclicBuffer.h"

class eClient : public ThreadRunner
{
	rpSelectorClient *selector;
	CyclicBuffer inBuf;
	CyclicBuffer outBuf;

public:
	eClient(std::string threadName, std::shared_ptr<ThreadPool> pool)
	: ThreadRunner(threadName, pool)
	{}
	virtual ~eClient() {
		if (selector)
		{
			selector->Done();
			delete selector;
		}
	}

	void Init()
	{
		selector = new rpSelectorClient("127.0.0.1", 5150, &inBuf, &outBuf, FD_CLOSE | FD_READ);
		selector->Init();
	}

	void Send(std::string str)
	{
		outBuf.Write(str);
	}

	std::string Read(std::string *str)
	{
		inBuf.Read();
	}

	void Done()
	{
		ThreadRunner::Done();
		if (selector)
		{
			selector->Done();
			delete selector;
		}
	}

protected:
	virtual void Task()
	{
		selector->Update();
	}

};