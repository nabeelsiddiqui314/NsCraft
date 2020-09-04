#pragma once
#include <memory>
#include <vector>

class IEventListener;
struct IEvent;

class Subject {
private:
	typedef std::weak_ptr<IEventListener> ListenerPtr;
public:
	Subject() = default;
	~Subject() = default;
public:
	void registerListener(const ListenerPtr& observer);
	void unregisterListener(const ListenerPtr& observer);

	void notifyListeners(IEvent& event);
private:
	std::vector<ListenerPtr> m_listeners;
};