#pragma once
#include "IState.h"
#include <memory>
#include "../Rendering/Camera/Camera.h"
#include <SFML/System/Vector2.hpp>
#include "../World/Blocks/BlockRegistry.h"
#include "../Rendering/ChunkRenderer.h"
#include "../Rendering/TextureAtlas.h"

class World;
class ChunkMeshingSystem;

class TestState : public IState {
public:
	TestState();
	~TestState() = default;
public:
	void handleEvent(StateMachine& stateMachine, const sf::Event& event) override;
	void update(StateMachine& stateMachine, float deltaTime) override;
	void render() override;
private:
	Camera m_camera;
	TextureAtlas m_textureAtlas;
	ChunkRenderer m_chunkRenderer;
	BlockRegistry m_blockRegistry;
	std::shared_ptr<World> m_world;
	std::shared_ptr<ChunkMeshingSystem> m_chunkMeshingSystem;

	sf::Vector2i m_lastMousePos;
};