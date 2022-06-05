#pragma once
#include "IState.h"
#include <memory>
#include "../Rendering/Camera/PerspectiveCamera.h"
#include "../Rendering/Camera/OrthographpicCamera.h"
#include <SFML/System/Vector2.hpp>
#include "../Rendering/ChunkRenderer.h"

class World;
class ChunkMeshingSystem;
class BlockLightingSystem;

class TestState : public IState {
public:
	TestState();
	~TestState() = default;
public:
	bool handleEvent(StateMachine& stateMachine, const sf::Event& event) override;
	void update(StateMachine& stateMachine, float deltaTime) override;
	void render() override;

	bool allowUpdateBelow() override;
	bool allowRenderingBelow() override;
private:
	PerspectiveCamera m_camera;
	OrthographicCamera m_orthoCamera;
	std::unique_ptr<ChunkRenderer> m_chunkRenderer;
	std::shared_ptr<World> m_world;
	std::shared_ptr<ChunkMeshingSystem> m_chunkMeshingSystem;
	std::shared_ptr<BlockLightingSystem> m_blockLightingSystem;

	sf::Vector2i m_lastMousePos;

	Vector3 m_blockAddPos;
	Vector3 m_blockRemovePos;
	bool m_canDig = false;
};