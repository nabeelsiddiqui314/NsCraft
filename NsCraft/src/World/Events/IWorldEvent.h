#pragma once

class IWorldObserver;

struct IWorldEvent {
public:
	IWorldEvent() = default;
	virtual ~IWorldEvent() = default;
public:
	virtual void handleEvent(IWorldObserver& eventHandler) const = 0;
};