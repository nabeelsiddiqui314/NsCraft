#pragma once
#include <functional>
#include <type_traits>
#include "Event.h"

class EventDispatcher {
private:
	template <typename T>
	using EventHandlerFn = std::function<void(T&)>;
public:
	EventDispatcher(IEvent& event) : m_event(event) {};
	~EventDispatcher() = default;
public:
	 template <typename T>
	 void dispatch(const EventHandlerFn<T>& eventHandler) {
		 static_assert(std::is_base_of<IEvent, T>::value);

		 if (m_event.getEventID() == IEvent::getUniqueEventID<T>()) {
			 eventHandler(static_cast<T&>(m_event));
		 }
	 }
private:
	IEvent& m_event;
};