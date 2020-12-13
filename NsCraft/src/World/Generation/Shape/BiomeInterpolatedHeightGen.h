#pragma once
#include "HeightmapGenerator.h"
#include "../../../Math/Noise.h"
#include "../Biome/BiomeDefs.h"

class IBiomeGenerator;
typedef std::shared_ptr<IBiomeGenerator> BiomeGenPtr;

class BiomeInterpolatedHeightGen : public HeightmapGenerator {
public:
	BiomeInterpolatedHeightGen(std::uint32_t seed, BiomeGenPtr biomeGenerator);
	~BiomeInterpolatedHeightGen() = default;
public:
	HeightmapPtr generateHeightmap(const Vector2& position, const BiomeMap& biomeMap) override;
private:
	float getHeightAt(const Vector2& chunkPosition, const Vector2& blockPosition);
	std::pair<Vector2, Vector2> getNeighborLocation(const Vector2& chunkPosition, 
		                                            const Vector2& blockPosition) const;

	float lerp(float x, float a, float b) const;
	float bilerp(float x, float y, float topLeft, float topRight, float bottomLeft, float bottomRight) const;
private:
	BiomeGenPtr m_biomeGenPtr;
	Noise m_heightNoise;
};