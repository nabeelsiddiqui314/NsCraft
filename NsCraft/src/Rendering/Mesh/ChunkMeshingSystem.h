#pragma once
#include <memory>
#include "../../EventSystem/IEventListener.h"

class World;
class BlockRegistry;
class TextureAtlas;
class ChunkRenderer;
struct Vector3;
struct ChunkLoadEvent;
struct ChunkUnloadEvent;
struct ChunkModifyEvent;

class ChunkMeshingSystem : public IEventListener {
public:
	ChunkMeshingSystem(const std::shared_ptr<World>& world, const BlockRegistry& blockRegistry, const TextureAtlas& textureAtlas, ChunkRenderer& renderer);
	~ChunkMeshingSystem() = default;
public:
	void onEvent(IEvent& event) override;
private:
	void onChunkLoad(ChunkLoadEvent& event) const;
	void onChunkUnload(ChunkUnloadEvent& event) const;
	void onChunkModify(ChunkModifyEvent& event) const;

	void meshChunk(const Vector3& chunkPosition) const;
	bool doesChunkHaveAllNeighbors(const Vector3& chunkPosition) const;
private:
	std::shared_ptr<World> m_world;
	const BlockRegistry& m_blockRegistry;
	const TextureAtlas& m_textureAtlas;
	ChunkRenderer& m_renderer;
};