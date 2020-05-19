#pragma once
#include <memory>
#include "IState.h"

class StateMachine {
public:
	StateMachine() = default;
	~StateMachine() = default;
public:
	template <typename T, typename... Args>
	void setState(Args&&... args) {
		m_currentState = std::make_unique<T>(std::forward<Args>(args)...);
	}

	void handleEvent(const sf::Event& event);
	void update(float deltaTime);
	void render();
private:
	std::unique_ptr<IState> m_currentState;
};