#include "World.h"
#include "Chunk.h"
#include "../Generation/ChunkGenerator/IChunkGenerator.h"
#include <algorithm>
#include "../Events/Events.h"
#include "../../Math/Directions.h"
#include "../../Math/CoordinateConversion.h"

World::World(ChunkGeneratorPtr&& chunkGenerator, int maxHeight) 
	: m_chunkGenerator(std::move(chunkGenerator)), m_maxHeight(maxHeight) {}

World::~World() {}

void World::loadChunk(const Vector3& position) {
	if (!doesChunkExist(position) && position.y >= 0 && position.y < m_maxHeight) {
		auto chunk = m_chunkGenerator->generateChunk(*this, position);
		m_chunkMap.emplace(std::make_pair(position, chunk));

		if (m_metaChunkMap.find(position) != m_metaChunkMap.end()) {
			m_metaChunkMap.at(position).applyModification(*chunk);
			m_metaChunkMap.erase(position);
		}

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

World::ChunkPtr World::getChunk(const Vector3& position) const {
	if (doesChunkExist(position)) {
		return m_chunkMap.at(position);
	}

	return nullptr;
}

void World::forEachChunk(const ForEachFunc& func) const {
	for (auto& [position, chunk] : m_chunkMap) {
		func(position);
	}
}

bool World::doesChunkExist(const Vector3& position) const {
	return m_chunkMap.find(position) != m_chunkMap.end();
}

bool World::doesChunkHaveAllNeighbors(const Vector3& position) {
	bool sideNeighbors = doesChunkExist(position + Directions::Right) &&
		                 doesChunkExist(position + Directions::Left) &&
		                 doesChunkExist(position + Directions::Front) &&
		                 doesChunkExist(position + Directions::Back);

	bool topNeighbor = doesChunkExist(position + Directions::Up);
	bool bottomNeighbor = doesChunkExist(position + Directions::Down);

	if (position.y == 0) {
		return sideNeighbors && topNeighbor;
	}

	if (position.y == m_maxHeight - 1) {
		return sideNeighbors && bottomNeighbor;
	}

	return sideNeighbors && topNeighbor && bottomNeighbor;
}

void World::setBlockIDAt(const Vector3& position, Block_ID blockID) {
	auto[chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		Block_ID previousBlockID = m_chunkMap.at(chunkPosition)->getBlock(blockPosition);
		if (previousBlockID != blockID) {
			m_chunkMap.at(chunkPosition)->setBlock(blockPosition, blockID);

			ChunkModifyEvent chunkModEvent;
			chunkModEvent.chunkPosition = chunkPosition;
			chunkModEvent.blockPosition = blockPosition;

			notifyObservers(chunkModEvent);

			BlockModifyEvent blockModEvent;
			blockModEvent.chunkPosition = chunkPosition;
			blockModEvent.blockPosition = blockPosition;
			blockModEvent.previousBlock = previousBlockID;
			blockModEvent.newBlock = blockID;

			notifyObservers(blockModEvent);
		}
	}
	else {
		m_metaChunkMap[chunkPosition].modifyBlock(blockPosition, blockID);
	}
}

Block_ID World::getBlockIDAt(const Vector3& position) const {
	auto [chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		return m_chunkMap.at(chunkPosition)->getBlock(blockPosition);
	}

	return 0;
}

void World::setSkyLightAt(const Vector3& position, std::uint8_t value) {
	auto [chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		m_chunkMap.at(chunkPosition)->setSkyLight(blockPosition, value);

		ChunkModifyEvent chunkModEvent;
		chunkModEvent.chunkPosition = chunkPosition;
		chunkModEvent.blockPosition = blockPosition;

		notifyObservers(chunkModEvent);
	}
}

void World::setNaturalLightAt(const Vector3& position, std::uint8_t value) {
	auto [chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		m_chunkMap.at(chunkPosition)->setNaturalLight(blockPosition, value);

		ChunkModifyEvent chunkModEvent;
		chunkModEvent.chunkPosition = chunkPosition;
		chunkModEvent.blockPosition = blockPosition;

		notifyObservers(chunkModEvent);
	}
}

std::uint8_t World::getSkyLightAt(const Vector3& position) const {
	auto [chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		return m_chunkMap.at(chunkPosition)->getSkyLight(blockPosition);
	}

	return 0;
}

std::uint8_t World::getNaturalLightAt(const Vector3& position) const {
	auto [chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		return m_chunkMap.at(chunkPosition)->getNaturalLight(blockPosition);
	}

	return 0;
}

bool World::isChunkFullyInvisible(const Vector3& position) const {
	if (doesChunkExist(position)) {
		return m_chunkMap.at(position)->isFullyInvisible();
	}

	return true;
}

bool World::isChunkFullyOpaque(const Vector3& position) const {
	if (doesChunkExist(position)) {
		return m_chunkMap.at(position)->isFullyOpaque();
	}

	return false;
}

int World::getMaxHeight() const {
	return m_maxHeight;
}

void World::registerObserver(const ObserverPtr& observer) {
	m_observers.emplace_back(observer);
}

std::pair<Vector3, Vector3> World::getBlockLocation(const Vector3& position) const {
	return CoordinateConversion::worldToChunk(position, Chunk::WIDTH);
}

void World::notifyObservers(IWorldEvent& event) {
	for (auto& observer : m_observers) {
		event.handleEvent(*observer.lock());
	}
}