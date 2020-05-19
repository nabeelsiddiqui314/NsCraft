#pragma once
#include <SFML/Window/Window.hpp>
#include <cstdint>
#include <string>

class Application {
public:
	Application(std::uint32_t windowWidth, std::uint32_t windowHeight, const std::string& windowName);
	~Application() = default;
public:
	int execute();
private:
	sf::Window m_window;
};