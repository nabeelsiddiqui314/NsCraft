#pragma once
#include "HeightmapGenerator.h"

class FlatHeightmapGenerator : public HeightmapGenerator {
public:
	FlatHeightmapGenerator(int height);
	~FlatHeightmapGenerator() = default;
public:
	HeightmapPtr generateHeightmap(const Vector2& position, const BiomeMap& biomeMap) override;
private:
	HeightmapPtr m_flatHeightmap;
};