#pragma once
#include "IBiomeGenerator.h"
#include "../../../Math/SimplexNoise.h"

class PerlinBiomeGenerator : public IBiomeGenerator {
public:
	PerlinBiomeGenerator(std::uint32_t seed);
	~PerlinBiomeGenerator() = default;
public:
	BiomeMapPtr generateBiome(const Vector2& position) override;
private:
	SimplexNoise m_landOceanNoise;
	SimplexNoise m_temperatureNoise;
	SimplexNoise m_rainfallNoise;
};