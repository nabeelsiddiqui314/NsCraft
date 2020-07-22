#include "Application.h"
#include <GL/glew.h>
#include <SFML/Window/Event.hpp>
#include "States/MenuState.h"

Application::Application(std::uint32_t windowWidth, std::uint32_t windowHeight, const std::string& windowName) {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 6;

	m_window.create(sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Default, settings);
	m_window.setActive();

	m_stateMachine.setState<MenuState>();
}

int Application::execute() {
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		return EXIT_FAILURE;
	}

	while (m_window.isOpen()) {
		sf::Event evnt;
		while (m_window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				m_window.close();
			}
			m_stateMachine.handleEvent(evnt);
		}

		m_stateMachine.update(m_deltaTimeClock.getElapsedTime().asSeconds());
		m_deltaTimeClock.restart();

		m_stateMachine.render();

		m_window.display();
	}

	return EXIT_SUCCESS;
}