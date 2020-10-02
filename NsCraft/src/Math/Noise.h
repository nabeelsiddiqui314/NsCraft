#pragma once
#include <cstdint>
#include <SFML/System/Vector2.hpp>

struct NoiseProperties {
	float octaves;
	float amplitude;
	float smoothness;
	float persistance;
	float lacunarity;
};

class Noise
{
public:
	Noise(std::uint32_t seed, const NoiseProperties& properties);
	~Noise() = default;
public:
	float getNoiseAt(const sf::Vector2f& position) const;
private:
	float getBasicNoise(const sf::Vector2f& position) const;
	float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) const;
	float lerp(float x, float a, float b) const;
	float fade(float t) const;
private:
	const std::uint32_t m_seed;
	NoiseProperties m_properties;
};