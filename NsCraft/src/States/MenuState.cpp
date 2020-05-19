#include "MenuState.h"
#include <GL/glew.h>
#include "SFML/Window/Event.hpp"
#include "StateMachine.h"
#include "GameState.h" 

void MenuState::handleEvent(StateMachine& stateMachine, const sf::Event& event) {
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
		stateMachine.setState<GameState>();
	}
}

void MenuState::update(StateMachine& stateMachine, float deltaTime) {

}

void MenuState::render() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
