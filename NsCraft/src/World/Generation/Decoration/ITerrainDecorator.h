#pragma once

struct Vector3;
class Chunk;
class World;
class Heightmap;

class ITerrainDecorator {
public:
	ITerrainDecorator() = default;
	virtual ~ITerrainDecorator() = default;
public:
	virtual void decorate(const Vector3& position, Chunk& chunk, const Heightmap& heightmap, World& world) = 0;
};