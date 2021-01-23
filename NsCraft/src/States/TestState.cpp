#include "TestState.h"
#include "SFML/Window/Event.hpp"
#include "StateMachine.h"
#include <GL/glew.h>

#include "../World/Chunk/World.h"
#include "../World/Blocks/BlockRegistry.h"
#include "../Rendering/Mesh/ChunkMeshingSystem.h"
#include "../Rendering/ChunkRenderer.h"
#include "../World/Blocks/Block.h"
#include "../Rendering/Mesh/CubeMeshGenerator.h"
#include "../World/Generation/ChunkGenerator/MonoBlockGenerator.h"
#include "../World/Generation/ChunkGenerator/RandomBlockGenerator.h"
#include "../World/Generation/ChunkGenerator/TerrainGenPipeline.h"
#include "../World/Generation/Shape/HeightmapGeneratorCache.h"
#include "../World/Generation/Shape/BiomeInterpolatedHeightGen.h"
#include "../World/Generation/Composition/BiomeInterpolatedComposer.h"
#include "../World/Chunk/Chunk.h"
#include "../Lighting/BlockLightingSystem.h"
#include "../Math/VoxelRaycast.h"
#include "../World/Generation/Biome/BiomeGeneratorCache.h"
#include "../World/Generation/Biome/PerlinBiomeGenerator.h"
#include "../World/Generation/Biome/BiomeRegistry.h"
#include "../World/Generation/Biome/Biome.h"
#include "../Lighting/LightDefs.h"
#include "../Rendering/Renderer.h"

TestState::TestState()
	: m_camera(800.0f / 600.0f, 80.0f), 
	  m_textureAtlas(16) {
	m_textureAtlas.addTexture("res/dirt.png", "dirt");
	m_textureAtlas.addTexture("res/grass_top.png", "grass_top");
	m_textureAtlas.addTexture("res/grass_side.png", "grass_side");
	m_textureAtlas.addTexture("res/bedrock.png", "bedrock");
	m_textureAtlas.addTexture("res/sand.png", "sand");

	auto texture = m_textureAtlas.generateAtlas();

	m_chunkRenderer = std::make_unique<ChunkRenderer>(texture);

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

	auto& sandBlock = blockRegistry.registerBlock("sand");
	sandBlock.setMeshGenerator(std::make_shared<CubeMeshGenerator>("sand", "sand", "sand"));
	sandBlock.setOpacity(LightDefs::MAX_OPACITY);

	auto& biomeRegistry = BiomeRegistry::getInstance();

	{
		auto& biome = biomeRegistry.registerBiome("plains");

		biome.setFlags(LAND);

		NoiseProperties prop;
		prop.octaves = 3;
		prop.smoothness = 800;
		prop.gain = 0.5f;
		prop.lacunarity = 4;
		prop.baseValue = 45;
		prop.variation = 30;

		prop.warpOctaves = 4;
		prop.warpFrequency = 0.015f;
		prop.warpLacunarity = 2.40f;
		prop.warpAmplitude = 22;;

		biome.setNoiseProperties(prop);

		ColumnComposition composition;
		composition = { blockRegistry.getBlockIDFromName("grass"),
						{ blockRegistry.getBlockIDFromName("dirt"), 3 },
						blockRegistry.getBlockIDFromName("bedrock") };

		biome.setComposition(composition);
	}

	{
		auto& biome = biomeRegistry.registerBiome("ocean");

		biome.setFlags(OCEAN);

		NoiseProperties prop;
		prop.octaves = 3;
		prop.smoothness = 500;
		prop.gain = 0.5f;
		prop.lacunarity = 4;
		prop.baseValue = 0;
		prop.variation = 30;

		prop.warpOctaves = 4;
		prop.warpFrequency = 0.009f;
		prop.warpLacunarity = 2.20f;
		prop.warpAmplitude = 18;

		biome.setNoiseProperties(prop);

		ColumnComposition composition;
		composition = {	{ blockRegistry.getBlockIDFromName("sand"), 3 },
						{ blockRegistry.getBlockIDFromName("dirt"), 5 },
						blockRegistry.getBlockIDFromName("bedrock") };

		biome.setComposition(composition);

	}

	auto biomeGen = std::make_shared<BiomeGeneratorCache>(std::make_unique<PerlinBiomeGenerator>(12212));
	auto shapeGen = std::make_shared<HeightmapGeneratorCache>(std::make_unique<BiomeInterpolatedHeightGen>(12212, biomeGen));
	auto composer = std::make_shared<BiomeInterpolatedComposer>();

	auto chunkGenerator = std::make_unique<TerrainGenPipeline>(biomeGen, shapeGen, composer);

	m_world = std::make_shared<World>(std::move(chunkGenerator), 10);
	m_chunkMeshingSystem = std::make_shared<ChunkMeshingSystem>(m_world, m_textureAtlas, *m_chunkRenderer);
	m_blockLightingSystem = std::make_shared<BlockLightingSystem>(m_world);

	m_world->registerListener(m_chunkMeshingSystem);
	m_world->registerListener(m_blockLightingSystem);

	Renderer::init();
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
		Renderer::resizeViewport(event.size.width, event.size.height);
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
	glClearColor(0.2f, 0.4f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Renderer::begin(m_camera);

	m_chunkRenderer->renderChunks(m_camera.getFrustum());
}

bool TestState::allowUpdateBelow() {
	return false;
}

bool TestState::allowRenderingBelow() {
	return false;
}
