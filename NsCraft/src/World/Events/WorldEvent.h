#pragma once
#include "IWorldObserver.h"

struct IWorldEvent {
public:
	virtual ~IWorldEvent() = default;
public:
	virtual void handleEvent(IWorldObserver& handler) = 0;
};

template <typename T>
struct WorldEvent : IWorldEvent {
	void handleEvent(IWorldObserver& handler) override {
		handler.onEvent(static_cast<T&>(*this));
	}
};