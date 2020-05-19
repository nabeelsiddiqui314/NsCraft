#include "MenuState.h"
#include <GL/glew.h>

void MenuState::handleEvent(StateMachine& machine, const sf::Event& event) {

}

void MenuState::update(StateMachine& machine, float deltaTime) {

}

void MenuState::render() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
