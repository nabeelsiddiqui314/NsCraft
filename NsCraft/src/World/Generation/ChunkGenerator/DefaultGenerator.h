#pragma once
#include "IChunkGenerator.h"
#include "../Heightmap.h"

class DefaultGenerator : public IChunkGenerator {
public:
	DefaultGenerator();
	~DefaultGenerator() = default;
public:
	std::shared_ptr<Chunk> generateChunk(const Vector3& position) override;
private:
	Heightmap m_heightMap;
};