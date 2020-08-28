#include "TestState.h"
#include <GL/glew.h>
#include "SFML/Window/Event.hpp"
#include "StateMachine.h"

#include "../World/Chunk/World.h"
#include "../World/Blocks/BlockRegistry.h"
#include "../Rendering/Mesh/ChunkMeshingSystem.h"
#include "../Rendering/ChunkRenderer.h"
#include "../World/Blocks/Block.h"
#include "../Rendering/Mesh/CubeMeshGenerator.h"
#include "../Rendering/Mesh/EmptyMeshGenerator.h"
#include "../World/ChunkGenerator/MonoBlockGenerator.h"
#include "../World/ChunkGenerator/RandomBlockGenerator.h"
#include "../World/Chunk/Chunk.h"

TestState::TestState()
	: m_blockRegistry(std::make_shared<BlockRegistry>()),
      m_chunkRenderer(std::make_shared<ChunkRenderer>()),
      m_camera(800.0f / 600.0f, 80.0f) {
	auto airBlock = std::make_shared<Block>(std::make_shared<EmptyMeshGenerator>(), false);
	m_blockRegistry->registerBlock("air", airBlock);

	auto testBlock = std::make_shared<Block>(std::make_shared<CubeMeshGenerator>(m_blockRegistry), true);
	m_blockRegistry->registerBlock("testBlock", testBlock);

	m_world = std::make_shared<World>(std::make_unique<RandomBlockGenerator>(std::vector<Block_ID>({ m_blockRegistry->getBlockIDFromName("air"),
																									m_blockRegistry->getBlockIDFromName("testBlock") })));
	m_chunkMeshingSystem = std::make_shared<ChunkMeshingSystem>(m_world, m_blockRegistry, m_chunkRenderer);

	m_world->addObserver(m_chunkMeshingSystem);

	int width = 5;
	int depth = 5;

	for (int y = 0; y < depth; y++) {
		for (int x = 0; x < width; x++) {
			for (int z = 0; z < width; z++) {
				m_world->loadChunk({x, y, z});
			}
		}
	}
}

void TestState::handleEvent(StateMachine& stateMachine, const sf::Event& event) {
	switch (event.type) {
	case sf::Event::MouseMoved:
		m_camera.rotate(event.mouseMove.x - m_lastMousePos.x, m_lastMousePos.y - event.mouseMove.y);
		m_lastMousePos = {event.mouseMove.x, event.mouseMove.y};
		break;
	case sf::Event::Resized:
		glViewport(0, 0, event.size.width, event.size.height);
		m_camera.setAspectRatio(static_cast<float>(event.size.width) / static_cast<float>(event.size.height));
		break;
	}
}
void TestState::update(StateMachine& stateMachine, float deltaTime) {
	const float speed = 20.0f * deltaTime;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_camera.move({0, speed, 0});
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		m_camera.move({ 0, -speed, 0 });
	}


	auto camFront = m_camera.getFront();
	camFront.y = 0;

	auto camRight = m_camera.getRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_camera.move(camFront * speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_camera.move(-camRight * speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_camera.move(-camFront * speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_camera.move(camRight * speed);
	}
}

void TestState::render() {
	glClearColor(0.0f, 1.0f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_chunkRenderer->renderChunks(m_camera);
}
