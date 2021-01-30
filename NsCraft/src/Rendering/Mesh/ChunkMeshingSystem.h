#pragma once
#include <memory>
#include <set>
#include "../../EventSystem/IEventListener.h"
#include "../../Utilities/ThreadPool.h"

class World;
class ChunkRenderer;
struct Vector3;
struct ChunkLoadEvent;
struct ChunkUnloadEvent;
struct ChunkModifyEvent;

class ChunkMeshingSystem : public IEventListener {
public:
	ChunkMeshingSystem(const std::shared_ptr<World>& world, ChunkRenderer& renderer);
	~ChunkMeshingSystem() = default;
public:
	void onEvent(IEvent& event) override;
	
	void generateChunkMeshes();
private:
	void onChunkLoad(ChunkLoadEvent& event);
	void onChunkUnload(ChunkUnloadEvent& event) const;
	void onChunkModify(ChunkModifyEvent& event);

	void enqueueChunkToMesh(const Vector3& chunkPosition);
	void meshChunk(const Vector3& chunkPosition);
	bool isChunkOccluded(const Vector3& position);
private:
	std::shared_ptr<World> m_world;
	ChunkRenderer& m_renderer;
	ThreadPool m_meshThreadPool;
	std::set<Vector3> m_chunksToMesh;
};