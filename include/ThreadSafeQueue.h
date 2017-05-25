#pragma once

#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "rp_libs.h"

template<typename T>
class RP_LIBS_API ThreadSafeQueue {
private:
	std::queue<T> dataQueue;
	std::mutex dataMutex;
	std::condition_variable dataConVar;

public:
	ThreadSafeQueue() = default;
	ThreadSafeQueue(ThreadSafeQueue& other);

	void			   push(T new_value);
	void			   waitAndPop(T& value);
	std::shared_ptr<T> waitAndPop();
	bool			   tryPop(T& value);
	std::shared_ptr<T> tryPop();
	bool			   empty();
};

template class RP_LIBS_API ThreadSafeQueue<int>;

