#pragma once
#include <memory>
#include <set>
#include "../../World/Events/IWorldObserver.h"
#include "../../Utilities/ThreadPool.h"

class World;
class ChunkRenderer;
struct Vector3;

class ChunkMeshingSystem : public IWorldObserver {
public:
	ChunkMeshingSystem(const std::shared_ptr<World>& world, ChunkRenderer& renderer);
	~ChunkMeshingSystem() = default;
public:
	void onEvent(const ChunkLoadEvent& event) override;
	void onEvent(const ChunkUnloadEvent& event) override;
	void onEvent(const ChunkModifyEvent& event) override;

	void generateChunkMeshes();
private:
	void enqueueChunkToMesh(const Vector3& chunkPosition);
	void meshChunk(const Vector3& chunkPosition);
	bool isChunkOccluded(const Vector3& position);
private:
	std::shared_ptr<World> m_world;
	ChunkRenderer& m_renderer;
	ThreadPool m_meshThreadPool;
	std::set<Vector3> m_chunksToMesh;
};