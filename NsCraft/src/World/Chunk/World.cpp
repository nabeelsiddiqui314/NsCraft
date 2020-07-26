#include "World.h"
#include "Chunk.h"
#include "../ChunkGenerator/IChunkGenerator.h"
#include "IWorldObserver.h"

void World::loadChunk(const Vector3& position) {
	if (!doesChunkExist(position)) {
		m_chunkMap.emplace(std::make_pair(position, m_chunkGenerator->generateChunk(position)));

		for (auto& observer : m_observers) {
			observer->onChunkLoad(position);
		}
	}
}

void World::unloadChunk(const Vector3& position) {
	if (doesChunkExist(position)) {
		m_chunkMap.erase(position);

		for (auto& observer : m_observers) {
			observer->onChunkUnload(position);
		}
	}
}

void World::addObserver(const WorldObserverPtr& observer) {
	m_observers.emplace_back(observer);
}

bool World::doesChunkExist(const Vector3& position) const {
	return m_chunkMap.find(position) != m_chunkMap.end();
}
