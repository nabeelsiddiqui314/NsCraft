#pragma once
#include "IHeightmapGenerator.h"
#include <unordered_map>
#include "../../../Math/Vector2.h"

class HeightmapGeneratorCache : public IHeightmapGenerator {
public:
	HeightmapGeneratorCache(std::unique_ptr<IHeightmapGenerator> heightmapGenerator);
	~HeightmapGeneratorCache() = default;
public:
	HeightmapPtr generateHeightmap(const Vector2& position, const BiomeMap& biomeMap) override;
private:
	std::unordered_map<Vector2, HeightmapPtr> m_heightmapCache;
	std::unique_ptr<IHeightmapGenerator> m_heightmapGenerator;
};