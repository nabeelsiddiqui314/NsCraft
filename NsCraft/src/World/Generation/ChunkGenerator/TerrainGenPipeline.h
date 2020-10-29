#pragma once
#include "IChunkGenerator.h"

class IDensityGenerator;

class TerrainGenPipeline : public IChunkGenerator {
public:
	TerrainGenPipeline() = default;
	~TerrainGenPipeline() = default;
public:
	std::shared_ptr<Chunk> generateChunk(World& world, const Vector3& position) override;
private:
	std::shared_ptr<IDensityGenerator> m_densityGenerator;
};