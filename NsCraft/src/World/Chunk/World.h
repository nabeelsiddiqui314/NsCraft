#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "../../Math/Vector3.h"
#include "../Blocks/BlockDefs.h"

class Chunk;
class IChunkGenerator;
class IWorldObserver;
struct IEvent;

class World {
private:
	typedef std::shared_ptr<Chunk> ChunkPtr;
	typedef std::weak_ptr<IWorldObserver> WorldObserverPtr;
	typedef std::unique_ptr<IChunkGenerator> ChunkGeneratorPtr;
public:
	World(ChunkGeneratorPtr&& chunkGenerator);
	~World();
public:
	void loadChunk(const Vector3& position);
	void unloadChunk(const Vector3& position);
	
	bool doesChunkExist(const Vector3& position) const;

	void addObserver(const WorldObserverPtr& observer);

	void setBlockIDAt(const Vector3& position, Block_ID blockID);
	Block_ID getBlockIDAt(const Vector3& position) const;
private:
	void notifyObservers(IEvent& event);

	// gets chunk position and block position from world position
	std::tuple<Vector3, Vector3> getBlockLocation(const Vector3& position) const;
private:
	std::unordered_map<Vector3, ChunkPtr> m_chunkMap;
	std::unique_ptr<IChunkGenerator> m_chunkGenerator;
	std::vector<WorldObserverPtr> m_observers;
};