#pragma once

#include <memory>

#include "rp_libs.h"

#include "ThreadControl.h"
#include "ThreadPool.h"

class ThreadPool;
class ThreadControl;

class RP_LIBS_API ThreadRunner
{
public:
	ThreadRunner(std::string threadName, std::shared_ptr<ThreadPool> pool);
	~ThreadRunner() = default;

	/* TODO: forbid assignments and moving */

	void Start();
	void Done();
	void Awake();
	void Stop();

	virtual void Task() = 0;

	std::string getThreadName() const;
	int getThreadID() const;
private:
	std::weak_ptr<ThreadControl> __threadControl;

	std::string __threadName;
	std::shared_ptr<ThreadPool> __pool;
};
