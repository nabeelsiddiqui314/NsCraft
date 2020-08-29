#include "World.h"
#include "Chunk.h"
#include "../ChunkGenerator/IChunkGenerator.h"
#include "IWorldObserver.h"
#include <algorithm>
#include "../Events/ChunkLoadEvent.h"
#include "../Events/ChunkUnloadEvent.h"
#include "../../EventSystem/Event.h"

World::World(ChunkGeneratorPtr&& chunkGenerator) 
	: m_chunkGenerator(std::move(chunkGenerator)) {}

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

		ChunkUnloadEvent event;
		event.chunkPosition = position;

		notifyObservers(event);
	}
}

bool World::doesChunkExist(const Vector3& position) const {
	return m_chunkMap.find(position) != m_chunkMap.end();
}

void World::addObserver(const WorldObserverPtr& observer) {
	m_observers.emplace_back(observer);
}

void World::setBlockIDAt(const Vector3& position, Block_ID blockID) {
	auto[chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		m_chunkMap.at(chunkPosition)->setBlock(blockPosition, blockID);
	}
}

Block_ID World::getBlockIDAt(const Vector3& position) const {
	auto [chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		return m_chunkMap.at(chunkPosition)->getBlock(blockPosition);
	}

	return 0;
}

void World::notifyObservers(IEvent& event) {
	auto isObserverExpired = [&](const WorldObserverPtr& observer) {
		return observer.expired();
	};

	m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(), isObserverExpired), m_observers.end());

	for (auto& observerPtr : m_observers) {
		auto observer = observerPtr.lock();
		observer->onEvent(event);
	}
}

std::tuple<Vector3, Vector3> World::getBlockLocation(const Vector3& position) const {
	const Vector3 chunkWidthVector = { Chunk::WIDTH, Chunk::WIDTH, Chunk::WIDTH };
	const auto& blockPosition = position % chunkWidthVector;
	const auto& chunkPosition = (position - blockPosition) / chunkWidthVector;

	return {chunkPosition, blockPosition};
}
