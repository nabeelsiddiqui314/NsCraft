#include "HeightmapGeneratorCache.h"
#include "Heightmap.h"

HeightmapGeneratorCache::HeightmapGeneratorCache(std::unique_ptr<HeightmapGenerator> heightmapGenerator) 
	: m_heightmapGenerator(std::move(heightmapGenerator)) {}

HeightmapPtr HeightmapGeneratorCache::generateHeightmap(const Vector2& position, const BiomeMap& biomeMap) {
	if (m_heightmapCache.find(position) == m_heightmapCache.end()) {
		m_heightmapCache.emplace(std::make_pair(position, m_heightmapGenerator->generateHeightmap(position, biomeMap)));
	}

	return m_heightmapCache.at(position);
}
