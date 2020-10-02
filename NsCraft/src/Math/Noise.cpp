#include "Noise.h"
#include "Noise.h"
#include <cmath>

Noise::Noise(std::uint32_t seed, const NoiseProperties& properties)
	: m_seed(seed),
	m_properties(properties) {}

float Noise::getNoiseAt(const sf::Vector2f& position) const {
	float amplitude = 1;
	float frequency = 1;
	float maxValue = 0;
	float total = 0;
	for (int i = 0; i < m_properties.octaves; i++) {
		total += amplitude * getBasicNoise(position * frequency);
		maxValue += amplitude;
		frequency *= m_properties.lacunarity;
		amplitude /= m_properties.persistance;
	}
	return total / maxValue;
}

float Noise::getBasicNoise(const sf::Vector2f& position) const {
	float x = position.x;
	float y = position.y;

	x /= m_properties.smoothness;
	y /= m_properties.smoothness;
	int xi = floor(x);
	int yi = floor(y);

	float xf = x - xi;
	float yf = y - yi;

	auto edgeVec = [&](int xOff, int yOff) {
		srand((xi + xOff) * 298773213 + (yi + yOff) * 907879988 + m_seed);
		float vx, vy;
		vx = -1 + rand() % 3;
		vy = -1 + rand() % 3;

		return sf::Vector2f({ vx, vy });
	};

	auto bLeftE = edgeVec(0, 0);
	auto bRightE = edgeVec(1, 0);
	auto fLeftE = edgeVec(0, 1);
	auto fRightE = edgeVec(1, 1);

	sf::Vector2f bLeftD =  { xf    , yf };
	sf::Vector2f bRightD = { xf - 1, yf };
	sf::Vector2f fLeftD =  { xf    , yf - 1 };
	sf::Vector2f fRightD = { xf - 1, yf - 1 };

	float bLeftDot = dot(bLeftE, bLeftD);
	float bRightDot = dot(bRightE, bRightD);
	float fLeftDot = dot(fLeftE, fLeftD);
	float fRightDot = dot(fRightE, fRightD);

	float u = fade(xf);
	float v = fade(yf);

	float xInter1 = lerp(u, bLeftDot, bRightDot);
	float xInter2 = lerp(u, fLeftDot, fRightDot);

	return m_properties.amplitude * ((lerp(v, xInter1, xInter2) + 1) / 2);
}

float Noise::dot(const sf::Vector2f& v1, const sf::Vector2f& v2) const {
	return v1.x * v2.x + v1.y * v2.y;
}

float Noise::lerp(float x, float a, float b) const {
	return a + x * (b - a);
}

float Noise::fade(float t) const {
	return 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
}