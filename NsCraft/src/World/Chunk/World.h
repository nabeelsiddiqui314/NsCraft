#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>
#include "../../EventSystem/Subject.h"
#include "../../Math/Vector3.h"
#include "../Blocks/BlockDefs.h"
#include <mutex>

class Chunk;
class IChunkGenerator;
struct IEvent;

class World : public Subject {
private:
	typedef std::shared_ptr<Chunk> ChunkPtr;
	typedef std::unique_ptr<IChunkGenerator> ChunkGeneratorPtr;
	typedef std::function<void(const Vector3&)> ForEachFunc;
public:
	World(ChunkGeneratorPtr&& chunkGenerator);
	~World();
public:
	void loadChunk(const Vector3& position);
	void unloadChunk(const Vector3& position);

	void forEachChunk(const ForEachFunc& func) const;
	
	bool doesChunkExist(const Vector3& position) const;

	void setBlockIDAt(const Vector3& position, Block_ID blockID);
	Block_ID getBlockIDAt(const Vector3& position) const;
private:
	// gets chunk position and block position from world position
	std::tuple<Vector3, Vector3> getBlockLocation(const Vector3& position) const;
private:
	std::unordered_map<Vector3, ChunkPtr> m_chunkMap;
	std::unique_ptr<IChunkGenerator> m_chunkGenerator;
	mutable std::mutex m_mutex;
};