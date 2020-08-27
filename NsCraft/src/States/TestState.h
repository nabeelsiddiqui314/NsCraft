#pragma once
#include "IState.h"
#include <memory>
#include "../Rendering/Camera/Camera.h"
#include <SFML/System/Vector2.hpp>

class World;
class BlockRegistry;
class ChunkMeshingSystem;
class ChunkRenderer;

class TestState : public IState {
public:
	TestState();
	~TestState() = default;
public:
	void handleEvent(StateMachine& stateMachine, const sf::Event& event) override;
	void update(StateMachine& stateMachine, float deltaTime) override;
	void render() override;
private:
	std::shared_ptr<BlockRegistry> m_blockRegistry;
	std::shared_ptr<ChunkRenderer> m_chunkRenderer;
	Camera m_camera;
	std::shared_ptr<World> m_world;
	std::shared_ptr<ChunkMeshingSystem> m_chunkMeshingSystem;

	sf::Vector2i m_lastMousePos;
};