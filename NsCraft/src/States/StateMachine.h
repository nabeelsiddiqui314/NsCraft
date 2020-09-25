#pragma once
#include <memory>
#include <vector>
#include "IState.h"

class StateMachine {
private:
	typedef std::unique_ptr<IState> StatePtr;
public:
	StateMachine() = default;
	~StateMachine() = default;
public:
	template <typename T, typename... Args>
	void pushState(Args&&... args) {
		m_stateStack.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
	}

	void popState();

	void handleEvent(const sf::Event& event);
	void update(float deltaTime);
	void render();
private:
	std::vector<StatePtr> m_stateStack;
};