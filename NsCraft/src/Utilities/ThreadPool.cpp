#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t numThreads) : m_stop(false) {
	for (std::size_t i = 0; i < numThreads; i++) {
		m_workerThreads.emplace_back([this]() {
			while (true) {
				Task task;

				{
					std::unique_lock<std::mutex> lock(m_mutex);
					m_workerCondition.wait(lock, [&]() {
						return !m_taskQueue.empty() || m_stop;
					});

					if (m_stop) {
						return;
					}

					task = m_taskQueue.front();
					m_taskQueue.pop();
				}

				task();
			}
		});
	}
}

ThreadPool::~ThreadPool() {
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_stop = true;
	}

	m_workerCondition.notify_all();

	for (auto& thread : m_workerThreads) {
		thread.join();
	}
}

void ThreadPool::enqueueTask(const Task& task) {
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_taskQueue.emplace(task);
	}

	m_workerCondition.notify_one();
}