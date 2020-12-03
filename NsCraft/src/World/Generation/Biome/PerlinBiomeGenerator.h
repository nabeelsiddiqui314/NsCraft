#pragma once
#include "IBiomeGenerator.h"
#include "../../../Math/Noise.h"

class PerlinBiomeGenerator : public IBiomeGenerator {
public:
	PerlinBiomeGenerator(std::uint32_t seed);
	~PerlinBiomeGenerator() = default;
public:
	BiomeMapPtr generateBiome(const Vector2& position) override;
private:
	Noise m_landOceanNoise;
	Noise m_temperatureNoise;
	Noise m_rainfallNoise;
};