#pragma once
#include <memory>

class Chunk;
class World;
struct Vector3;

class IChunkGenerator {
public:
	IChunkGenerator() = default;
	virtual ~IChunkGenerator() = default;
public:
	virtual std::shared_ptr<Chunk> generateChunk(World& world, const Vector3& position) = 0;
};