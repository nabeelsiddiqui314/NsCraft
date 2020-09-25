#include "StateMachine.h"

void StateMachine::popState() {
	m_stateStack.pop_back();
}

void StateMachine::handleEvent(const sf::Event& event) {
	for (auto iter = m_stateStack.rbegin(); iter != m_stateStack.rend(); iter++) {
		auto& state = *iter;
		bool eventHandled = state->handleEvent(*this, event);

		if (eventHandled || !state->allowUpdateBelow()) {
			break;
		}
	}
}

void StateMachine::update(float deltaTime) {
	for (auto iter = m_stateStack.rbegin(); iter != m_stateStack.rend(); iter++) {
		auto& state = *iter;

		state->update(*this, deltaTime);

		if (!state->allowUpdateBelow()) {
			break;
		}
	}
}

void StateMachine::render() {
	std::size_t renderingBeginIndex = 0;

	for (std::size_t i = m_stateStack.size() - 1; i >= 0; i--) {
		renderingBeginIndex = i;

		if (!m_stateStack[i]->allowRenderingBelow()) {
			break;
		}
	}

	for (std::size_t i = renderingBeginIndex; i < m_stateStack.size(); i++) {
		m_stateStack[i]->render();
	}
}