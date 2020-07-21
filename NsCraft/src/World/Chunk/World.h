#pragma once
#include <memory>
#include <unordered_map>
#include "../../Math/Vector3.h"

class Chunk;
class IChunkGenerator;

class World {
public:
	typedef std::shared_ptr<Chunk> ChunkPtr;
public:
	World() = default;
	~World() = default;
public:
	void loadChunk(const Vector3& position);
	void unloadChunk(const Vector3& position);

	const ChunkPtr& getChunk(const Vector3& position) const;
private:
	bool doesChunkExist(const Vector3& position) const;
private:
	std::unordered_map<Vector3, ChunkPtr> m_chunkMap;
	std::unique_ptr<IChunkGenerator> m_chunkGenerator;
};