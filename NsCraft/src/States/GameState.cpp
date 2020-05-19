#include "GameState.h"
#include <GL/glew.h>
#include "SFML/Window/Event.hpp"
#include "MenuState.h"
#include "StateMachine.h"

void GameState::handleEvent(StateMachine& stateMachine, const sf::Event& event) {
	
}

void GameState::update(StateMachine& stateMachine, float deltaTime) {

}

void GameState::render() {
	glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
