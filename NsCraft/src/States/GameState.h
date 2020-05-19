#pragma once
#include "IState.h"

class GameState : public IState {
public:
	GameState() = default;
	~GameState() = default;
public:
	void handleEvent(StateMachine& stateMachine, const sf::Event& event) override;
	void update(StateMachine& stateMachine, float deltaTime) override;
	void render() override;
};