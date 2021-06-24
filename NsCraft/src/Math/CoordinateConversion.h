#pragma once
#include <utility>
#include "Vector2.h"
#include "Vector3.h"

namespace CoordinateConversion {
	Vector2 chunkToWorld(const Vector2& chunkCoords, const Vector2& localCoords, int chunkWidth);
	Vector3 chunkToWorld(const Vector3& chunkCoords, const Vector3& localCoords, int chunkWidth);

	std::pair<Vector2, Vector2> worldToChunk(const Vector2& worldCoords, int chunkWidth);
	std::pair<Vector3, Vector3> worldToChunk(const Vector3& worldCoords, int chunkWidth);
}