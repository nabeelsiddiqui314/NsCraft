#pragma once

namespace sf {
	class Event;
}

class StateMachine;

class IState {
public:
	IState() = default;
	virtual ~IState() {}
public:
	virtual void handleEvent(StateMachine& stateMachine, const sf::Event& event) {}
	virtual void update(StateMachine& stateMachine, float deltaTime) = 0;
	virtual void render() = 0;

	virtual bool allowUpdateBelow() = 0;
	virtual bool allowRenderingBelow() = 0;
};