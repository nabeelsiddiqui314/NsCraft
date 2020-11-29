#pragma once
#include <cstdint>
#include <SFML/System/Vector2.hpp>

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
	float getBasicNoise(const sf::Vector2f& position) const;
	float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) const;
	float lerp(float x, float a, float b) const;
	float fade(float t) const;
private:
	std::uint32_t m_seed;
	NoiseProperties m_properties;
};