#pragma once

#include <thread>
#include <string>

class ThreadRAII
{
public:
	enum class DtorAction { join, detach };

	ThreadRAII(std::thread&& t, DtorAction action = DtorAction::join);
	~ThreadRAII();

	std::thread& get();
private:
	DtorAction __action;
	std::string __threadName;
	std::thread __t;
};