#include "StateMachine.h"

void StateMachine::popState() {
	m_stateStack.pop_back();
}

void StateMachine::handleEvent(const sf::Event& event) {
	reverseIterate([&](const StatePtr& state) {
		state->handleEvent(*this, event);
		return state->allowUpdateBelow();
	});
}

void StateMachine::update(float deltaTime) {
	reverseIterate([&](const StatePtr& state) {
		state->update(*this, deltaTime);
		return state->allowUpdateBelow();
	});
}

void StateMachine::render() {
	reverseIterate([&](const StatePtr& state) {
		state->render();
		return state->allowRenderingBelow();
	});
}

void StateMachine::reverseIterate(const ReverseIterateFunc& reverseIterate) {
	for (auto iter = m_stateStack.rbegin(); iter != m_stateStack.rend(); iter++) {
		if (!reverseIterate(*iter)) {
			break;
		}
	}
}