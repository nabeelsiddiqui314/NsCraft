#pragma once
#include <SFML/Window/Window.hpp>
#include <cstdint>
#include <string>
#include "States/StateMachine.h"
#include <SFML/System/Clock.hpp>

class Application {
public:
	Application(std::uint32_t windowWidth, std::uint32_t windowHeight, const std::string& windowName);
	~Application() = default;
public:
	int execute();
private:
	sf::Window m_window;
	StateMachine m_stateMachine;
	sf::Clock m_deltaTimeClock;
};