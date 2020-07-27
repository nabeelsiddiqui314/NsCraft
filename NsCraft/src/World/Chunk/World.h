#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "../../Math/Vector3.h"

class Chunk;
class IChunkGenerator;
class IWorldObserver;

class World {
private:
	typedef std::shared_ptr<Chunk> ChunkPtr;
	typedef std::weak_ptr<IWorldObserver> WorldObserverPtr;

	enum class WorldEvent {
		CHUNK_LOAD,
		CHUNK_UNLOAD
	};
public:
	World() = default;
	~World() = default;
public:
	void loadChunk(const Vector3& position);
	void unloadChunk(const Vector3& position);

	void addObserver(const WorldObserverPtr& observer);
private:
	bool doesChunkExist(const Vector3& position) const;
	void notifyObservers(const Vector3& position, const WorldEvent& event);
private:
	std::unordered_map<Vector3, ChunkPtr> m_chunkMap;
	std::unique_ptr<IChunkGenerator> m_chunkGenerator;
	std::vector<WorldObserverPtr> m_observers;
};