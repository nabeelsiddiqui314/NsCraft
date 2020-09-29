#pragma once
#include <memory>

class Chunk;
struct Vector3;

class IChunkGenerator {
public:
	IChunkGenerator() = default;
	virtual ~IChunkGenerator() = default;
public:
	virtual std::shared_ptr<Chunk> generateChunk(const Vector3& position) = 0;
};