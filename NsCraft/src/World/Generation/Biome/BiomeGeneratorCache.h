#pragma once
#include "IBiomeGenerator.h"
#include <unordered_map>
#include "../../../Math//Vector2.h"

// decorator of biome generator that caches biomeMaps

class BiomeGeneratorCache : public IBiomeGenerator {
public:
	BiomeGeneratorCache(std::unique_ptr<IBiomeGenerator> biomeGenerator);
	~BiomeGeneratorCache() = default;
public:
	BiomeMapPtr generateBiome(const Vector2& position) override;
private:
	std::unique_ptr<IBiomeGenerator> m_biomeGenerator;
	std::unordered_map<Vector2, BiomeMapPtr> m_biomeMapCache;
};