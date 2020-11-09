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
#include "../World/Generation/ChunkGenerator/TerrainGenPipeline.h"
#include "../World/Generation/Shape/HeightmapGenerator.h"
#include "../World/Generation/Composition/DefaultComposer.h"
#include "../World/Chunk/Chunk.h"
#include "../Lighting/BlockLightingSystem.h"

TestState::TestState()
	: m_camera(800.0f / 600.0f, 80.0f), 
	  m_textureAtlas(16) {
	m_textureAtlas.addTexture("res/dirt.png", "dirt");
	m_textureAtlas.addTexture("res/grass_top.png", "grass_top");
	m_textureAtlas.addTexture("res/grass_side.png", "grass_side");
	m_textureAtlas.addTexture("res/bedrock.png", "bedrock");
	m_textureAtlas.generateAtlas();

	auto& blockRegistry = BlockRegistry::getInstance();

	auto& airBlock = blockRegistry.registerBlock("air");

	auto& grassBlock = blockRegistry.registerBlock("grass");
	grassBlock.setMeshGenerator(std::make_shared<CubeMeshGenerator>("grass_top", "grass_side", "dirt"));
	grassBlock.setOpaqueness(true);

	auto& dirtBlock = blockRegistry.registerBlock("dirt");
	dirtBlock.setMeshGenerator(std::make_shared<CubeMeshGenerator>("dirt", "dirt", "dirt"));
	dirtBlock.setOpaqueness(true);

	auto& bedrock = blockRegistry.registerBlock("bedrock");
	bedrock.setMeshGenerator(std::make_shared<CubeMeshGenerator>("bedrock", "bedrock", "bedrock"));
	bedrock.setOpaqueness(true);

	auto& lightTest = blockRegistry.registerBlock("lightTest");
	lightTest.setMeshGenerator(std::make_shared<CubeMeshGenerator>("bedrock", "bedrock", "bedrock"));
	lightTest.setOpaqueness(true);
	lightTest.setLuminocity(15);

	NoiseProperties noiseProperties;
	noiseProperties.octaves = 3;
	noiseProperties.amplitude = 200;
	noiseProperties.smoothness = 150;
	noiseProperties.persistance = 4;
	noiseProperties.lacunarity = 4;

	auto chunkGenerator = std::make_unique<TerrainGenPipeline>(std::make_shared<HeightmapGenerator>(12212, noiseProperties),
		                                                       std::make_shared<DefaultComposer>());

	m_world = std::make_shared<World>(std::move(chunkGenerator));
	m_chunkMeshingSystem = std::make_shared<ChunkMeshingSystem>(m_world, m_textureAtlas, m_chunkRenderer);
	m_blockLightingSystem = std::make_shared<BlockLightingSystem>(m_world);

	m_world->registerListener(m_chunkMeshingSystem);
	m_world->registerListener(m_blockLightingSystem);
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
	const float speed = 50.0f * deltaTime;
	
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

	int loadDistance = 16;
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

	if (m_world->getBlockIDAt(camPos) != 0) {
		m_world->setBlockIDAt(camPos, 4);
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
