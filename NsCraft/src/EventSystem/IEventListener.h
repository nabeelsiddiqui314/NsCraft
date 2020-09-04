#pragma once

struct IEvent;

class IEventListener {
public:
	IEventListener() = default;
	virtual ~IEventListener() = default;
public:
	virtual void onEvent(IEvent& event) = 0;
};