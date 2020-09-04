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
	ChunkMeshingSystem(const std::shared_ptr<World>& world, const std::shared_ptr<BlockRegistry>& blockRegistry, 
		const std::shared_ptr<ChunkRenderer>& renderer);
	~ChunkMeshingSystem() = default;
public:
	void onEvent(IEvent& event) override;
private:
	void onChunkLoad(ChunkLoadEvent& event) const;
	void onChunkUnload(ChunkUnloadEvent& event) const;

	bool doesChunkHaveAllNeighbors(const Vector3& chunkPosition) const;
private:
	std::shared_ptr<World> m_world;
	std::shared_ptr<BlockRegistry> m_blockRegistry;
	std::shared_ptr<ChunkRenderer> m_renderer;
};