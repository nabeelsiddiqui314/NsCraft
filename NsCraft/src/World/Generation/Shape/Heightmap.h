#pragma once
#include <array>
#include "../../Chunk/Chunk.h"

struct Vector2;

class Heightmap {
public:
	Heightmap() = default;
	~Heightmap() = default;
public:
	void setHeightAt(const Vector2& position, int height);
	int getHeightAt(const Vector2& position) const;
private:
	inline std::size_t getIndex(const Vector2& position) const;
private:
	std::array<int, Chunk::WIDTH* Chunk::WIDTH> m_heightMap;
};