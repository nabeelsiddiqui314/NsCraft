#include "BiomeGeneratorCache.h"
#include "BiomeMap.h"

BiomeGeneratorCache::BiomeGeneratorCache(std::unique_ptr<IBiomeGenerator> biomeGenerator) 
	: m_biomeGenerator(std::move(biomeGenerator)) {}

BiomeMapPtr BiomeGeneratorCache::generateBiome(const Vector2& position) {
	if (m_biomeMapCache.find(position) == m_biomeMapCache.end()) {
		m_biomeMapCache.emplace(std::make_pair(position, m_biomeGenerator->generateBiome(position)));
	}

	return m_biomeMapCache.at(position);
}