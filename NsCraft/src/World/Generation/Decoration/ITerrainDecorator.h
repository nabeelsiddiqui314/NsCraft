#pragma once

struct Vector3;
class Chunk;
class World;

class ITerrainDecorator {
public:
	ITerrainDecorator() = default;
	virtual ~ITerrainDecorator() = default;
public:
	virtual void decorate(const Vector3& position, Chunk& chunk, World& world) = 0;
};