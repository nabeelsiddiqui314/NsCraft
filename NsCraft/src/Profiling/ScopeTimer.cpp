#include "ScopeTimer.h"
#include <iostream>

ScopeTimer::ScopeTimer(const std::string& taskName) 
	: m_taskName(taskName),
      m_hasStopped(false) {
	m_start = std::chrono::high_resolution_clock::now();
}

ScopeTimer::~ScopeTimer() {
	stop();
}

void ScopeTimer::stop() {
	if (!m_hasStopped) {
		m_finish = std::chrono::high_resolution_clock::now();

		using millisecond = std::chrono::duration<double, std::milli>;
		auto elapsedTime = std::chrono::duration_cast<millisecond>(m_finish - m_start);

		std::cout << m_taskName << " has completed in " << std::to_string(elapsedTime.count()) << "ms" << std::endl;

		m_hasStopped = true;
	}
}