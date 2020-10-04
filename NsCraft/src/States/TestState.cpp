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
#include "../World/Generation/ChunkGenerator/MonoBlockGenerator.h"
#include "../World/Generation/ChunkGenerator/RandomBlockGenerator.h"
#include "../World/Generation/ChunkGenerator/DefaultGenerator.h"
#include "../World/Chunk/Chunk.h"

TestState::TestState()
	: m_camera(800.0f / 600.0f, 80.0f), 
	  m_textureAtlas(16) {
	m_textureAtlas.addTexture("res/dirt.png", "dirt");
	m_textureAtlas.addTexture("res/grass_top.png", "grass_top");
	m_textureAtlas.addTexture("res/grass_side.png", "grass_side");
	m_textureAtlas.generateAtlas();

	auto& airBlock = m_blockRegistry.registerBlock("air");

	auto& grassBlock = m_blockRegistry.registerBlock("grass");
	grassBlock.setMeshGenerator(std::make_shared<CubeMeshGenerator>("grass_top", "grass_side", "dirt"));
	grassBlock.setOpaqueness(true);

	auto& dirtBlock = m_blockRegistry.registerBlock("dirt");
	dirtBlock.setMeshGenerator(std::make_shared<CubeMeshGenerator>("dirt", "dirt", "dirt"));
	dirtBlock.setOpaqueness(true);

	m_world = std::make_shared<World>(std::make_unique<DefaultGenerator>());
	m_chunkMeshingSystem = std::make_shared<ChunkMeshingSystem>(m_world, m_blockRegistry, m_textureAtlas, m_chunkRenderer);

	m_world->registerListener(m_chunkMeshingSystem);
}

bool TestState::handleEvent(StateMachine& stateMachine, const sf::Event& event) {
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

	return false;
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

	int loadDistance = 8;
	int height = 16;

	int chunkPosX = m_camera.getPosition().x / Chunk::WIDTH;
	int chunkPosZ = m_camera.getPosition().z / Chunk::WIDTH;

	for (int y = 0; y < height; y++) {
		for (int x = chunkPosX - loadDistance; x < chunkPosX + loadDistance; x++) {
			for (int z = chunkPosZ - loadDistance; z < chunkPosZ + loadDistance; z++) {
				m_world->loadChunk({ x, y, z });
			}
		}
	}

	m_world->forEachChunk([&](const Vector3& position) {
		if (position.x < chunkPosX - loadDistance || position.x > chunkPosX + loadDistance ||
			position.z < chunkPosZ - loadDistance || position.z > chunkPosZ + loadDistance) {
			m_world->unloadChunk(position);
		}
	});

	Vector3 camPos = Vector3(m_camera.getPosition().x ,m_camera.getPosition().y, m_camera.getPosition().z);

	for (int y = camPos.y - 3; y < camPos.y + 3; y++) {
		for (int x = camPos.x - 3; x < camPos.x + 3; x++) {
			for (int z = camPos.z - 3; z < camPos.z + 3; z++) {
				m_world->setBlockIDAt({x, y, z}, 0);
			}
		}
	}

	m_chunkMeshingSystem->generateChunkMeshes();
}

void TestState::render() {
	glClearColor(0.0f, 1.0f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_textureAtlas.bindTexture();
	m_chunkRenderer.renderChunks(m_camera);
}

bool TestState::allowUpdateBelow() {
	return false;
}

bool TestState::allowRenderingBelow() {
	return false;
}
