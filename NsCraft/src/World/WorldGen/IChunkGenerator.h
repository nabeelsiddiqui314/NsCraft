#pragma once
#include <memory>

class Chunk;

class IChunkGenerator {
public:
	IChunkGenerator() = default;
	virtual ~IChunkGenerator() = default;
public:
	virtual std::shared_ptr<Chunk> generateChunk() = 0;
};