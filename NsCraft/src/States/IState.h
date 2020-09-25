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
	virtual bool handleEvent(StateMachine& stateMachine, const sf::Event& event) = 0;
	virtual void update(StateMachine& stateMachine, float deltaTime) = 0;
	virtual void render() = 0;

	virtual bool allowUpdateBelow() = 0;
	virtual bool allowRenderingBelow() = 0;
};