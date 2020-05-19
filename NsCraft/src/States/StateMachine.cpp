#include "StateMachine.h"

void StateMachine::handleEvent(const sf::Event& event) {
	m_currentState->handleEvent(*this, event);
}

void StateMachine::update(float deltaTime) {
	m_currentState->update(*this, deltaTime);
}

void StateMachine::render() {
	m_currentState->render();
}
