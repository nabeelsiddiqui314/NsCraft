#pragma once
#include "IDensityGenerator.h"
#include "../Heightmap.h"

class HeightmapGenerator : public IDensityGenerator {
public:
	HeightmapGenerator(std::uint32_t seed, const NoiseProperties& noiseProperties);
	~HeightmapGenerator() = default;
public:
	DensityMapPtr generateDensityMap(const Vector3& position) override;
private:
	Heightmap m_heightmap;
};