#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "../../Math/Vector3.h"
#include "../ChunkGenerator/ChunkGeneratorFactory.h"

class Chunk;
class IChunkGenerator;
class IWorldObserver;
struct IWorldEvent;

class World {
private:
	typedef std::shared_ptr<Chunk> ChunkPtr;
	typedef std::weak_ptr<IWorldObserver> WorldObserverPtr;
public:
	World();
	explicit World(const ChunkGeneratorType& type);
	~World();
public:
	void loadChunk(const Vector3& position);
	void unloadChunk(const Vector3& position);
	
	bool doesChunkExist(const Vector3& position) const;

	void addObserver(const WorldObserverPtr& observer);
private:
	void notifyObservers(const IWorldEvent& event);
private:
	std::unordered_map<Vector3, ChunkPtr> m_chunkMap;
	std::unique_ptr<IChunkGenerator> m_chunkGenerator;
	ChunkGeneratorFactory m_chunkGeneratorfactory;
	std::vector<WorldObserverPtr> m_observers;
};