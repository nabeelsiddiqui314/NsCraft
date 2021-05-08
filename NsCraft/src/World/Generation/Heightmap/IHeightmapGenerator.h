#pragma once
#include <memory>

struct Vector2;
class Heightmap;
class BiomeMap;

typedef std::shared_ptr<Heightmap> HeightmapPtr;

class IHeightmapGenerator {
public:
	IHeightmapGenerator() = default;
	virtual ~IHeightmapGenerator() = default;
public:
	virtual HeightmapPtr generateHeightmap(const Vector2& position, const BiomeMap& biomeMap) = 0;
};