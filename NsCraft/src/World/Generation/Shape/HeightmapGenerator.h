#pragma once
#include "IShapeGenerator.h"
#include "../HeightmapCache.h"
#include "../../../Math/Noise.h"

class HeightmapGenerator : public IShapeGenerator {
public:
	HeightmapGenerator(std::uint32_t seed, const NoiseProperties& noiseProperties);
	~HeightmapGenerator() = default;
public:
	ChunkShapePtr generateShape(const Vector3& position, const BiomeMap& biomeMap) override;
private:
	HeightmapCache m_heightmap;
	Noise m_noise;
};