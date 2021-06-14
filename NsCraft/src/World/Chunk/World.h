#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>
#include "../../Math/Vector3.h"
#include "../Blocks/BlockDefs.h"
#include "MetaChunk.h"

class Chunk;
class IChunkGenerator;
class IWorldObserver;
struct IWorldEvent;

class World {
private:
	typedef std::shared_ptr<Chunk> ChunkPtr;
	typedef std::unique_ptr<IChunkGenerator> ChunkGeneratorPtr;
	typedef std::function<void(const Vector3&)> ForEachFunc;
	typedef std::weak_ptr<IWorldObserver> ObserverPtr;
public:
	World(ChunkGeneratorPtr&& chunkGenerator, int maxHeight);
	~World();
public:
	void loadChunk(const Vector3& position);
	void unloadChunk(const Vector3& position);

	ChunkPtr getChunk(const Vector3& position) const;

	void forEachChunk(const ForEachFunc& func) const;
	
	bool doesChunkExist(const Vector3& position) const;
	bool doesChunkHaveAllNeighbors(const Vector3& position);

	void setBlockIDAt(const Vector3& position, Block_ID blockID);
	Block_ID getBlockIDAt(const Vector3& position) const;

	void setSkyLightAt(const Vector3& position, std::uint8_t value);
	void setNaturalLightAt(const Vector3& position, std::uint8_t value);

	std::uint8_t getSkyLightAt(const Vector3& position) const;
	std::uint8_t getNaturalLightAt(const Vector3& position) const;

	bool isChunkFullyInvisible(const Vector3& position) const;
	bool isChunkFullyOpaque(const Vector3& position) const;
	
	int getMaxHeight() const;

	void registerObserver(const ObserverPtr& observer);
private:
	// gets chunk position and block position from world position
	std::tuple<Vector3, Vector3> getBlockLocation(const Vector3& position) const;

	void notifyObservers(IWorldEvent& event);
private:
	std::unordered_map<Vector3, ChunkPtr> m_chunkMap;
	std::unordered_map<Vector3, MetaChunk> m_metaChunkMap;
	std::unique_ptr<IChunkGenerator> m_chunkGenerator;
	const int m_maxHeight;

	std::vector<ObserverPtr> m_observers;
};