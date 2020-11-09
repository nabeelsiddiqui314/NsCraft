#pragma once
#include <memory>
#include <queue>
#include "../EventSystem/IEventListener.h"
#include "../Math/Vector3.h"

class World;
struct Vector3;
struct BlockModifiedEvent;

class BlockLightingSystem : public IEventListener {
public:
	BlockLightingSystem(const std::shared_ptr<World>& world);
	~BlockLightingSystem() = default;
public:
	void onEvent(IEvent& event) override;
private:
	void onBlockModified(BlockModifiedEvent& event);

	void propogateLight(const Vector3& startBlockPosition, std::uint8_t luminocity);
	void spreadToNeighbor(const Vector3& neighborPos, std::uint8_t lightValue);
	bool doesChunkHaveAllNeighbors(const Vector3& chunkPosition);
private:
	std::shared_ptr<World> m_world;
	std::queue<Vector3> m_lightBfsQueue;
};