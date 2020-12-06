#include "Noise.h"
#include "Vector2.h"
#include <glm/gtc/noise.hpp>

Noise::Noise()
	: m_seed(0) {}

Noise::Noise(std::uint32_t seed, const NoiseProperties& properties)
	: m_seed(seed),
	m_properties(properties) {}

void Noise::setSeed(std::uint32_t seed) {
	m_seed = seed;
}

void Noise::setNoiseProperties(const NoiseProperties& properties) {
	m_properties = properties;
}

float Noise::getNoiseAt(const Vector2& position) const {
	float amplitude = 1;
	float frequency = 1;
	float maxValue = 0;
	float total = 0;
	for (int i = 0; i < m_properties.octaves; i++) {
		auto position2f = glm::vec2(position.x, position.y);

		float noise = glm::simplex(position2f / m_properties.smoothness * frequency);

		// converts -1 -> 1 to 0 -> 1
		noise += 1.0f;
		noise /= 2.0f;

		noise *= m_properties.amplitude;

		total += amplitude * noise;
		maxValue += amplitude;
		frequency *= m_properties.lacunarity;
		amplitude /= m_properties.persistance;
	}
	return total / maxValue;
}