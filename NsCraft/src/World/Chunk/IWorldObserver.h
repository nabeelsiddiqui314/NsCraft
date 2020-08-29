#pragma once

struct Vector3;
struct IEvent;

class IWorldObserver {
public:
	IWorldObserver() = default;
	virtual ~IWorldObserver() = default;
public:
	virtual void onEvent(IEvent& event) {}
};