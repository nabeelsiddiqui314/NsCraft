#include "World.h"
#include "Chunk.h"
#include "../WorldGen/IChunkGenerator.h"

void World::loadChunk(const Vector3& position) {
	if (!doesChunkExist(position)) {
		m_chunkMap.emplace(std::make_pair(position, m_chunkGenerator->generateChunk(position)));
	}
}

void World::unloadChunk(const Vector3& position) {
	m_chunkMap.erase(position);
}

bool World::doesChunkExist(const Vector3& position) const {
	return m_chunkMap.find(position) != m_chunkMap.end();
}
