#pragma once

#include <memory>
#include <map>

#include "rp_libs.h"

#include "ThreadControl.h"
#include "ThreadRunner.h"

static const int MAX_THREADS = 10;

class ThreadControl;
class ThreadRunner;

class RP_LIBS_API ThreadPool
{
public:
	ThreadPool(int max_threads = MAX_THREADS);
	~ThreadPool();

	std::weak_ptr<ThreadControl> createThread(ThreadRunner* runner);

	void StartAll();
	void StopAll();
	void AwakeAll();
	void DoneAll();

	void showAllIDs() const;
	void showAllNames() const;

	/* TODO: duplicated strings */
	ThreadRunner* getRunnerByName(std::string&);
	ThreadRunner* getRunnerByID(unsigned int);

private:
	int __max_threads;
	std::map<int, std::shared_ptr<ThreadControl> > __threads;

};