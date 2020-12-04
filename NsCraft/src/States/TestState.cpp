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
#include "../World/Generation/Shape/FlatHeightmapGenerator.h"
#include "../World/Generation/Composition/DefaultComposer.h"
#include "../World/Chunk/Chunk.h"
#include "../Lighting/BlockLightingSystem.h"
#include "../Math/VoxelRaycast.h"
#include "../World/Generation/Biome/BiomeGeneratorCache.h"
#include "../World/Generation/Biome/PerlinBiomeGenerator.h"
#include "../World/Generation/Biome/BiomeRegistry.h"
#include "../World/Generation/Biome/Biome.h"
#include "../Lighting/LightDefs.h"

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
	grassBlock.setOpacity(LightDefs::MAX_OPACITY);

	auto& dirtBlock = blockRegistry.registerBlock("dirt");
	dirtBlock.setMeshGenerator(std::make_shared<CubeMeshGenerator>("dirt", "dirt", "dirt"));
	dirtBlock.setOpacity(LightDefs::MAX_OPACITY);

	auto& bedrock = blockRegistry.registerBlock("bedrock");
	bedrock.setMeshGenerator(std::make_shared<CubeMeshGenerator>("bedrock", "bedrock", "bedrock"));
	bedrock.setOpacity(LightDefs::MAX_OPACITY);

	auto& lightTest = blockRegistry.registerBlock("lightTest");
	lightTest.setMeshGenerator(std::make_shared<CubeMeshGenerator>("bedrock", "bedrock", "bedrock"));
	lightTest.setOpacity(LightDefs::MAX_OPACITY);
	lightTest.setLuminocity(LightDefs::MAX_LUMINOCITY);

	NoiseProperties noiseProperties;
	noiseProperties.octaves = 3;
	noiseProperties.amplitude = 200;
	noiseProperties.smoothness = 150; 
	noiseProperties.persistance = 4;
	noiseProperties.lacunarity = 4;

	auto& biomeRegistry = BiomeRegistry::getInstance();

	{
		auto& biome = biomeRegistry.registerBiome("plains");

		biome.setFlags(LAND);

		NoiseProperties prop;
		prop.octaves = 3;
		prop.amplitude = 80;
		prop.smoothness = 150;
		prop.persistance = 4;
		prop.lacunarity = 4;

		biome.setNoiseProperties(prop);
	}

	{
		auto& biome = biomeRegistry.registerBiome("ocean");

		biome.setFlags(OCEAN);

		NoiseProperties prop;
		prop.octaves = 3;
		prop.amplitude = 30;
		prop.smoothness = 50;
		prop.persistance = 4;
		prop.lacunarity = 4;

		biome.setNoiseProperties(prop);
	}

	auto chunkGenerator = std::make_unique<TerrainGenPipeline>(std::make_shared<BiomeGeneratorCache>(std::make_unique<PerlinBiomeGenerator>(12212)),
		                                                       std::make_shared<FlatHeightmapGenerator>(50),
		                                                       std::make_shared<DefaultComposer>());

	m_world = std::make_shared<World>(std::move(chunkGenerator), 10);
	m_chunkMeshingSystem = std::make_shared<ChunkMeshingSystem>(m_world, m_textureAtlas, m_chunkRenderer);
	m_blockLightingSystem = std::make_shared<BlockLightingSystem>(m_world);

	m_world->registerListener(m_chunkMeshingSystem);
	m_world->registerListener(m_blockLightingSystem);
}

bool TestState::handleEvent(StateMachine& stateMachine, const sf::Event& event) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (m_canDig) {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				m_world->setBlockIDAt(m_blockRemovePos, 0);
			}
			else if (event.mouseButton.button == sf::Mouse::Button::Right) {
				m_world->setBlockIDAt(m_blockAddPos, 4);
			}
			else if(event.mouseButton.button == sf::Mouse::Button::Middle) {
				m_world->setBlockIDAt(m_blockAddPos, 2);
			}
		}
		break;
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

	Vector3 camPos = Vector3(floor(m_camera.getPosition().x), floor(m_camera.getPosition().y), floor(m_camera.getPosition().z));

	VoxelRaycast ray(m_camera.getPosition(), m_camera.getFront());

	Vector3 lastPos = camPos;

	for (int i = 0; i < 10; i++) {
		auto newPos = ray.increment();

		if (m_world->getBlockIDAt(lastPos) == 0 &&
			m_world->getBlockIDAt(newPos) != 0) {
			m_blockAddPos = lastPos;
			m_blockRemovePos = newPos;
			m_canDig = true;
			break;
		}

		lastPos = newPos;

		m_canDig = false;
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
