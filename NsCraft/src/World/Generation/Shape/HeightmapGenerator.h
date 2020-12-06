#pragma once
#include "IShapeGenerator.h"

struct Vector2;
class Heightmap;

typedef std::shared_ptr<Heightmap> HeightmapPtr;

class HeightmapGenerator : public IShapeGenerator {
public:
	HeightmapGenerator() = default;
	virtual ~HeightmapGenerator() = default;
public:
	ChunkShapePtr generateShape(const Vector3& position, const BiomeMap& biomeMap) override;
	virtual HeightmapPtr generateHeightmap(const Vector2& position, const BiomeMap& biomeMap) = 0;
};