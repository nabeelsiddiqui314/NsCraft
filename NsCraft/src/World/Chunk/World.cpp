#include "World.h"
#include "Chunk.h"
#include "../ChunkGenerator/IChunkGenerator.h"
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

void World::forEachChunk(const ForEachFunc& func) const {
	for (auto& [position, chunk] : m_chunkMap) {
		func(position);
	}
}

bool World::doesChunkExist(const Vector3& position) const {
	return m_chunkMap.find(position) != m_chunkMap.end();
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

std::tuple<Vector3, Vector3> World::getBlockLocation(const Vector3& position) const {
	Vector3 chunkWidthVector = { Chunk::WIDTH, Chunk::WIDTH, Chunk::WIDTH };
	auto blockPosition = position % chunkWidthVector;

	if (blockPosition.x < 0) {
		blockPosition.x = abs(blockPosition.x);
		blockPosition.x = Chunk::WIDTH - blockPosition.x;
	}

	if (blockPosition.y < 0) {
		blockPosition.y = abs(blockPosition.y);
		blockPosition.y = Chunk::WIDTH - blockPosition.y;
	}

	if (blockPosition.z < 0) {
		blockPosition.z = abs(blockPosition.z);
		blockPosition.z = Chunk::WIDTH - blockPosition.z;
	}

	const auto& chunkPosition = (position - blockPosition) / chunkWidthVector;

	return {chunkPosition, blockPosition};
}
