#pragma once
#include "Vector2.h"

struct CellularData {
	Vector2 nearestSeed;
	float distanceToPoint;
};

class CellularNoise {
public:
	CellularNoise() = default;
	CellularNoise(int seed, int cellWidth, int jitter);

	~CellularNoise() = default;
public:
	void setSeed(int seed);
	void setCellwidth(int cellWidth);
	void setJitter(int jitter);

	CellularData getNoiseAt(const Vector2& position) const;
private:
	Vector2 randomOffsetVector(const Vector2& position) const;

	int distanceSquared(const Vector2& p1, const Vector2& p2) const;
private:
	int m_seed;
	int m_cellWidth;
	int m_jitter;
};