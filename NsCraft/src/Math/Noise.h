#pragma once
#include <cstdint>

struct Vector2;

struct NoiseProperties {
	float octaves = 0.0f;
	float amplitude = 0.0f;
	float smoothness = 0.0f;
	float persistance = 0.0f;
	float lacunarity = 0.0f;
};

class Noise
{
public:
	Noise();
	Noise(std::uint32_t seed, const NoiseProperties& properties);
	~Noise() = default;
public:
	void setSeed(std::uint32_t seed);
	void setNoiseProperties(const NoiseProperties& properties);

	float getNoiseAt(const Vector2& position) const;
private:
	std::uint32_t m_seed;
	NoiseProperties m_properties;
};