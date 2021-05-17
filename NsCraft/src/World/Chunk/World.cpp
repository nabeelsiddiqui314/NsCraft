#include "World.h"
#include "Chunk.h"
#include "../Generation/ChunkGenerator/IChunkGenerator.h"
#include <algorithm>
#include "../Events/ChunkLoadEvent.h"
#include "../Events/ChunkUnloadEvent.h"
#include "../Events/ChunkModifyEvent.h"
#include "../Events/BlockModifiedEvent.h"
#include "../../EventSystem/Event.h"
#include "../../Math/Directions.h"

World::World(ChunkGeneratorPtr&& chunkGenerator, int maxHeight) 
	: m_chunkGenerator(std::move(chunkGenerator)), m_maxHeight(maxHeight) {}

World::~World() {}

void World::loadChunk(const Vector3& position) {
	if (!doesChunkExist(position) && position.y >= 0 && position.y < m_maxHeight) {
		auto chunk = m_chunkGenerator->generateChunk(*this, position);
		m_chunkMap.emplace(std::make_pair(position, chunk));

		if (m_metaChunkMap.find(position) != m_metaChunkMap.end()) {
			m_metaChunkMap.at(position).applyModification(chunk);
			m_metaChunkMap.erase(position);
		}

		ChunkLoadEvent event;
		event.chunkPosition = position;

		notifyListeners(event);
	}
}

void World::unloadChunk(const Vector3& position) {
	if (doesChunkExist(position)) {
		m_chunkMap.erase(position);

		ChunkUnloadEvent event;
		event.chunkPosition = position;

		notifyListeners(event);
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

			notifyListeners(chunkModEvent);

			BlockModifiedEvent blockModEvent;
			blockModEvent.chunkPosition = chunkPosition;
			blockModEvent.blockPosition = blockPosition;
			blockModEvent.previousBlock = previousBlockID;
			blockModEvent.newBlock = blockID;

			notifyListeners(blockModEvent);
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

		notifyListeners(chunkModEvent);
	}
}

void World::setNaturalLightAt(const Vector3& position, std::uint8_t value) {
	auto [chunkPosition, blockPosition] = getBlockLocation(position);

	if (doesChunkExist(chunkPosition)) {
		m_chunkMap.at(chunkPosition)->setNaturalLight(blockPosition, value);

		ChunkModifyEvent chunkModEvent;
		chunkModEvent.chunkPosition = chunkPosition;
		chunkModEvent.blockPosition = blockPosition;

		notifyListeners(chunkModEvent);
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

std::tuple<Vector3, Vector3> World::getBlockLocation(const Vector3& position) const {
	Vector3 chunkPosition;
	chunkPosition.x = floor((float)position.x / (float)Chunk::WIDTH);
	chunkPosition.y = floor((float)position.y / (float)Chunk::WIDTH);
	chunkPosition.z = floor((float)position.z / (float)Chunk::WIDTH);

	auto blockPosition = position - chunkPosition * Chunk::WIDTH;

	return { chunkPosition, blockPosition };
}
