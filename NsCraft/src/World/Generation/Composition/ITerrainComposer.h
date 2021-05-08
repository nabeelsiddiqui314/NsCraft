#pragma once

struct Vector3;
class Chunk;
class Heightmap;
class BiomeMap;

class ITerrainComposer {
public:
	ITerrainComposer() = default;
	virtual ~ITerrainComposer() = default;
public:
	virtual void compose(const Vector3& position, Chunk& chunk, const Heightmap& heightmap, const BiomeMap& biomeMap) = 0;
};