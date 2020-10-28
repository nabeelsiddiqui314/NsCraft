#pragma once
#include "IChunkGenerator.h"

class TerrainGenPipeline : public IChunkGenerator {
public:
	TerrainGenPipeline() = default;
	~TerrainGenPipeline() = default;
public:
	std::shared_ptr<Chunk> generateChunk(World& world, const Vector3& position) override;
private:

};