#pragma once
#include "IState.h"

class MenuState : public IState {
public:
public:
	void handleEvent(StateMachine& machine, const sf::Event& event);
	void update(StateMachine& machine, float deltaTime) override;
	void render() override;
};