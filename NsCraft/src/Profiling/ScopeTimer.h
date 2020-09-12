#pragma once
#include <string>
#include <chrono>

class ScopeTimer {
private:
	typedef std::chrono::high_resolution_clock::time_point TimePoint;
public:
	ScopeTimer(const std::string& taskName);
	~ScopeTimer();

	ScopeTimer(const ScopeTimer&) = delete;
	ScopeTimer& operator=(const ScopeTimer&) = delete;
	ScopeTimer(ScopeTimer&&) = delete;
public:
	void stop();
private:
	const std::string m_taskName;
	TimePoint m_start, m_finish;
	bool m_hasStopped;
};