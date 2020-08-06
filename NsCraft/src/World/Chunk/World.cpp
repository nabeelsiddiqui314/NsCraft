#include "World.h"
#include "Chunk.h"
#include "../ChunkGenerator/IChunkGenerator.h"
#include "IWorldObserver.h"
#include <algorithm>
#include "../Events/IWorldEvent.h"
#include "../Events/ChunkLoadEvent.h"
#include "../Events/ChunkUnloadEvent.h"

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

		ChunkLoadEvent event;
		event.chunkPosition = position;

		notifyObservers(event);
	}
}

void World::unloadChunk(const Vector3& position) {
	if (doesChunkExist(position)) {
		m_chunkMap.erase(position);

		ChunkLoadEvent event;
		event.chunkPosition = position;

		notifyObservers(event);
	}
}

void World::addObserver(const WorldObserverPtr& observer) {
	m_observers.emplace_back(observer);
}

bool World::doesChunkExist(const Vector3& position) const {
	return m_chunkMap.find(position) != m_chunkMap.end();
}

void World::notifyObservers(const IWorldEvent& event) {
	auto isObserverExpired = [&](const WorldObserverPtr& observer) {
		return observer.expired();
	};

	m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(), isObserverExpired), m_observers.end());

	for (auto& observerPtr : m_observers) {
		auto observer = observerPtr.lock();

		event.handleEvent(*observer);
	}
}
