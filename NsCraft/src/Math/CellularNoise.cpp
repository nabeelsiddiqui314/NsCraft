#include "CellularNoise.h"
#include <math.h>
#include <limits.h>
#include <glm/glm.hpp>

CellularNoise::CellularNoise(int seed, int cellWidth, int jitter) 
	: m_seed(seed),
      m_cellWidth(cellWidth), 
      m_jitter(jitter) {}

void CellularNoise::setSeed(int seed) {
	m_seed = seed;
}

void CellularNoise::setCellwidth(int cellWidth) {
	m_cellWidth = cellWidth;
}

void CellularNoise::setJitter(int jitter) {
	m_jitter = jitter;
}

CellularData CellularNoise::getNoiseAt(const Vector2& position) const {
	Vector2 centrePosition;
	centrePosition.x = floor((float)position.x / (float)m_cellWidth);
	centrePosition.y = floor((float)position.y / (float)m_cellWidth);

	Vector2 nearestSeed;
	int minDist = INT_MAX;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			Vector2 cellPosition = centrePosition + Vector2(x, y);
			Vector2 cellSeed = cellPosition * m_cellWidth + randomOffsetVector(cellPosition);

			int distance = distanceSquared(position, cellSeed);

			if (distance < minDist) {
				minDist = distance;
				nearestSeed = cellSeed;
			}
		}
	}

	CellularData data;
	data.nearestSeed = nearestSeed;
	data.distanceToPoint = sqrt(minDist);

	return data;
}

Vector2 CellularNoise::randomOffsetVector(const Vector2& position) const {
	glm::vec2 position2f(position.x, position.y);
	glm::vec2 offset = glm::fract(glm::sin(glm::vec2(glm::dot(position2f, glm::vec2(127.1f, 311.7f)), glm::dot(position2f, glm::vec2(269.5f, 183.3f))) * 43758.5453f * (float)m_seed));

	offset *= (float)m_jitter;

	return Vector2(offset.x, offset.y);
}

int CellularNoise::distanceSquared(const Vector2& p1, const Vector2& p2) const {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
