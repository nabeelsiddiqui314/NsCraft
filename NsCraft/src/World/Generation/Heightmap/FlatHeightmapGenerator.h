#pragma once
#include "IHeightmapGenerator.h"

class FlatHeightmapGenerator : public IHeightmapGenerator {
public:
	FlatHeightmapGenerator(int height);
	~FlatHeightmapGenerator() = default;
public:
	HeightmapPtr generateHeightmap(const Vector2& position, const BiomeMap& biomeMap) override;
private:
	HeightmapPtr m_flatHeightmap;
};