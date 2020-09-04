#include "Subject.h"
#include <algorithm>
#include "IEventListener.h"

void Subject::registerListener(const ListenerPtr& listener) {
	m_listeners.push_back(listener);
}

void Subject::unregisterListener(const ListenerPtr& listener) {
	auto isListenerEqual = [&](const ListenerPtr& other) {
		return listener.lock() == other.lock();
	};

	m_listeners.erase(std::remove_if(m_listeners.begin(), m_listeners.end(), isListenerEqual), m_listeners.end());
}

void Subject::notifyListeners(IEvent& event) {
	auto isListenerExpired = [&](const ListenerPtr& listener) {
		return listener.expired();
	};

	m_listeners.erase(std::remove_if(m_listeners.begin(), m_listeners.end(), isListenerExpired), m_listeners.end());

	for (auto& listenerPtr : m_listeners) {
		auto listener = listenerPtr.lock();
		listener->onEvent(event);
	}
}
