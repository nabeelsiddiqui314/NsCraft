#pragma once
#include <cstdint>
#include <FastNoiseLite.h>

struct Vector2;

struct NoiseProperties {
	int octaves = 0;
	float smoothness = 0.0f;
	float gain = 0.0f;
	float lacunarity = 0.0f;
	float baseValue = 0.0f;
	float variation = 0.0f;

	int warpOctaves = 0;
	float warpAmplitude = 0.0f;
	float warpFrequency = 0.0f;
	float warpLacunarity = 0.0f;
	float warpGain = 0.0f;
};

class SimplexNoise
{
public:
	SimplexNoise();
	SimplexNoise(int seed, const NoiseProperties& properties);
	~SimplexNoise() = default;
public:
	void setSeed(int seed);
	void setNoiseProperties(const NoiseProperties& properties);

	float getNoiseAt(const Vector2& position);
private:
	FastNoiseLite m_noiseGenerator;
	FastNoiseLite m_domainWarper;
	NoiseProperties m_properties;
};