#pragma once
#include "HeightmapGenerator.h"
#include <unordered_map>
#include "../../../Math/Vector2.h"

class HeightmapGeneratorCache : public HeightmapGenerator {
public:
	HeightmapGeneratorCache(std::unique_ptr<HeightmapGenerator> heightmapGenerator);
	~HeightmapGeneratorCache() = default;
public:
	HeightmapPtr generateHeightmap(const Vector2& position) override;
private:
	std::unordered_map<Vector2, HeightmapPtr> m_heightmapCache;
	std::unique_ptr<HeightmapGenerator> m_heightmapGenerator;
};