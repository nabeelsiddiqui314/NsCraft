#include "HeightmapCache.h"


void HeightmapCache::setHeightAt(const Vector2& chunkPosition, const Vector2& blockPosition, int height) {
	m_heightmapCacheMap[chunkPosition][getIndex(blockPosition)] = height;
}

int HeightmapCache::getHeightAt(const Vector2& chunkPosition, const Vector2& blockPosition) const {
	if (doesHeightMapExist(chunkPosition)) {
		return m_heightmapCacheMap.at(chunkPosition)[getIndex(blockPosition)];
	} 
	
	return 0;
}

bool HeightmapCache::doesHeightMapExist(const Vector2& position) const {
	return m_heightmapCacheMap.find(position) != m_heightmapCacheMap.end();
}

std::size_t HeightmapCache::getIndex(const Vector2& blockPosition) const {
	return blockPosition.x + blockPosition.y * Chunk::WIDTH;
}