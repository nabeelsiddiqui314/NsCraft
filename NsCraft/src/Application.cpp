#include "Application.h"
#include <GL/glew.h>
#include <SFML/Window/Event.hpp>

Application::Application(std::uint32_t windowWidth, std::uint32_t windowHeight, const std::string& windowName) {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 6;

	m_window.create(sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Default, settings);
	m_window.setActive();
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
		}

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_window.display();
	}

	return EXIT_SUCCESS;
}