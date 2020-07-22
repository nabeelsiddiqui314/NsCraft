#pragma once
#include "IState.h"

class MenuState : public IState {
public:
	MenuState() = default;
	~MenuState() = default;
public:
	void handleEvent(StateMachine& stateMachine, const sf::Event& event) override;
	void update(StateMachine& stateMachine, float deltaTime) override;
	void render() override;
};