#include <SFML/Window.hpp>
#include <GL/glew.h>

int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 6;

	sf::Window window(sf::VideoMode(1280, 720), "NsCraft", sf::Style::Default, settings);
	window.setActive(true);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		return EXIT_FAILURE;
	}

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}
		}

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window.display();
	}

	return EXIT_SUCCESS;
}