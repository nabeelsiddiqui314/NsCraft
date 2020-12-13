#pragma once
#include "../../../Utilities/Flat2DArray.h"
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
	Flat2DArray<int, Chunk::WIDTH, Chunk::WIDTH> m_heightMap;
};