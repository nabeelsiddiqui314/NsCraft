#pragma once
#include <queue>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

class ThreadPool {
private:
	typedef std::function<void()> Task;
public:
	ThreadPool(std::size_t numThreads);
	~ThreadPool();
public:
	void enqueueTask(const Task& task);
private:
	std::queue<Task> m_taskQueue;
	std::mutex m_mutex;
	std::vector<std::thread> m_workerThreads;
	std::condition_variable m_workerCondition;
	bool m_stop;
};