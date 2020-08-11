#pragma once
#include <memory>
#include "../World/Chunk/IWorldObserver.h"

class World;
class BlockRegistry;

class ChunkRenderer : public IWorldObserver {
public:
	ChunkRenderer(const std::shared_ptr<World>& world, const std::shared_ptr<BlockRegistry>& blockRegistry);
	~ChunkRenderer() = default;
public:
	void onWorldEvent(const ChunkLoadEvent& event) override;
	void onWorldEvent(const ChunkUnloadEvent& event) override;
private:
	bool doesChunkHaveAllNeighbors(const Vector3& chunkPosition) const;
private:
	std::shared_ptr<World> m_world;
	std::shared_ptr<BlockRegistry> m_blockRegistry;
};