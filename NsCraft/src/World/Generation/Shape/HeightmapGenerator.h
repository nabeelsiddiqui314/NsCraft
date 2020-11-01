#pragma once
#include "IShapeGenerator.h"
#include "../Heightmap.h"

class HeightmapGenerator : public IShapeGenerator {
public:
	HeightmapGenerator(std::uint32_t seed, const NoiseProperties& noiseProperties);
	~HeightmapGenerator() = default;
public:
	ChunkShapePtr generateShape(const Vector3& position) override;
private:
	Heightmap m_heightmap;
};