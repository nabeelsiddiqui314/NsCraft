#pragma once
#include <memory>
#include "../../EventSystem/IEventListener.h"

class World;
class BlockRegistry;
class ChunkRenderer;
struct Vector3;
struct ChunkLoadEvent;
struct ChunkUnloadEvent;

class ChunkMeshingSystem : public IEventListener {
public:
	ChunkMeshingSystem(const std::shared_ptr<World>& world, const BlockRegistry& blockRegistry, ChunkRenderer& renderer);
	~ChunkMeshingSystem() = default;
public:
	void onEvent(IEvent& event) override;
private:
	void onChunkLoad(ChunkLoadEvent& event) const;
	void onChunkUnload(ChunkUnloadEvent& event) const;

	bool doesChunkHaveAllNeighbors(const Vector3& chunkPosition) const;
private:
	std::shared_ptr<World> m_world;
	const BlockRegistry& m_blockRegistry;
	ChunkRenderer& m_renderer;
};