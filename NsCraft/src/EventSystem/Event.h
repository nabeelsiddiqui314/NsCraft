#pragma once
#include <cstdint>

typedef std::uint32_t Event_ID;

struct IEvent {
	friend class EventDispatcher;
protected:
	virtual Event_ID getEventID() const = 0;

	template <typename T>
	static Event_ID getUniqueEventID()  {
		static Event_ID id{ generateNewEventID() };
		return id;
	}
private:
	static Event_ID generateNewEventID() {
		static Event_ID id{ 0 };
		return id++;
	}
};

template <typename T>
struct Event : IEvent {
private:
	Event_ID getEventID() const override {
		return getUniqueEventID<T>();
	}
};