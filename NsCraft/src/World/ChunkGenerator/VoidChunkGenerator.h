#pragma once
#include "IChunkGenerator.h"

class VoidChunkGenerator : public IChunkGenerator {
public:
	VoidChunkGenerator() = default;
	~VoidChunkGenerator() = default;
public:
	std::shared_ptr<Chunk> generateChunk(const Vector3& position) override;
};