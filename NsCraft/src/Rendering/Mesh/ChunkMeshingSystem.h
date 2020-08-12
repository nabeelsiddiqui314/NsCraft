#pragma once
#include <memory>
#include "../../World/Chunk/IWorldObserver.h"

class World;
class BlockRegistry;
class ChunkRenderer;

class ChunkMeshingSystem : public IWorldObserver {
public:
	ChunkMeshingSystem(const std::shared_ptr<World>& world, const std::shared_ptr<BlockRegistry>& blockRegistry, 
		const std::shared_ptr<ChunkRenderer>& renderer);
	~ChunkMeshingSystem() = default;
public:
	void onWorldEvent(const ChunkLoadEvent& event) override;
	void onWorldEvent(const ChunkUnloadEvent& event) override;
private:
	bool doesChunkHaveAllNeighbors(const Vector3& chunkPosition) const;
private:
	std::shared_ptr<World> m_world;
	std::shared_ptr<BlockRegistry> m_blockRegistry;
	std::shared_ptr<ChunkRenderer> m_renderer;
};