#include "World.h"
#include "Chunk.h"
#include "../ChunkGenerator/IChunkGenerator.h"
#include "IWorldObserver.h"
#include <algorithm>

World::World() {
	m_chunkGenerator = m_chunkGeneratorfactory.createChunkGenerator(ChunkGeneratorType::VOID);
}

World::World(const ChunkGeneratorType& type) {
	m_chunkGenerator = m_chunkGeneratorfactory.createChunkGenerator(type);
}

World::~World() {}

void World::loadChunk(const Vector3& position) {
	if (!doesChunkExist(position)) {
		m_chunkMap.emplace(std::make_pair(position, m_chunkGenerator->generateChunk(position)));

		notifyObservers(position, WorldEvent::CHUNK_LOAD);
	}
}

void World::unloadChunk(const Vector3& position) {
	if (doesChunkExist(position)) {
		m_chunkMap.erase(position);

		notifyObservers(position, WorldEvent::CHUNK_UNLOAD);
	}
}

void World::addObserver(const WorldObserverPtr& observer) {
	m_observers.emplace_back(observer);
}

bool World::doesChunkExist(const Vector3& position) const {
	return m_chunkMap.find(position) != m_chunkMap.end();
}

void World::notifyObservers(const Vector3& position, const WorldEvent& event) {
	auto isObserverExpired = [&](const WorldObserverPtr& observer) {
		return observer.expired();
	};

	m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(), isObserverExpired), m_observers.end());

	for (auto& observerPtr : m_observers) {
		auto observer = observerPtr.lock();

		switch (event)
		{
		case WorldEvent::CHUNK_LOAD:
			observer->onChunkLoad(position);
			break;
		case WorldEvent::CHUNK_UNLOAD:
			observer->onChunkUnload(position);
			break;
		default:
			break;
		}
	}
}
