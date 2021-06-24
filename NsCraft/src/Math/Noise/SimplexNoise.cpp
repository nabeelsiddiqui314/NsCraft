#include "SimplexNoise.h"
#include "../Vector2.h"
#include <glm/gtc/noise.hpp>

SimplexNoise::SimplexNoise() {
	m_noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
	m_noiseGenerator.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);
	m_domainWarper.SetDomainWarpType(FastNoiseLite::DomainWarpType::DomainWarpType_OpenSimplex2Reduced);
	m_domainWarper.SetFractalType(FastNoiseLite::FractalType::FractalType_DomainWarpIndependent);
}

SimplexNoise::SimplexNoise(int seed, const NoiseProperties& properties) : SimplexNoise() {
	setSeed(seed);
	setNoiseProperties(properties);
}

void SimplexNoise::setSeed(int seed) {
	m_noiseGenerator.SetSeed(seed);
	m_domainWarper.SetSeed(seed);
}

void SimplexNoise::setNoiseProperties(const NoiseProperties& properties) {
	m_properties = properties;

	m_noiseGenerator.SetFractalOctaves(properties.octaves);
	m_noiseGenerator.SetFrequency(1.0f / properties.smoothness);
	m_noiseGenerator.SetFractalLacunarity(properties.lacunarity);
	m_noiseGenerator.SetFractalGain(properties.gain);

	m_domainWarper.SetDomainWarpAmp(properties.warpAmplitude);
	m_domainWarper.SetFrequency(properties.warpFrequency);
	m_domainWarper.SetFractalOctaves(properties.warpOctaves);
	m_domainWarper.SetFractalLacunarity(properties.warpLacunarity);
	m_domainWarper.SetFractalGain(properties.warpGain);
}

float SimplexNoise::getNoiseAt(const Vector2& position) {
	float x = position.x;
	float y = position.y;

	m_domainWarper.DomainWarp(x, y);

	float noise = m_noiseGenerator.GetNoise(x, y);

	// converts -1 -> 1 to 0 -> 1
	noise += 1.0f;
	noise /= 2.0f;

	noise *= m_properties.variation;
	noise += m_properties.baseValue;

	return noise;
}