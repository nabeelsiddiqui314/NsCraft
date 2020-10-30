#pragma once
#include "IChunkGenerator.h"
#include <memory>
#include <vector>

class IDensityGenerator;
class ITerrainComposer;
class ITerrainDecorator;

class TerrainGenPipeline : public IChunkGenerator {
private:
	typedef std::shared_ptr<IDensityGenerator> DensityGeneratorPtr;
	typedef std::shared_ptr<ITerrainComposer> TerrainComposerPtr;
	typedef std::shared_ptr<ITerrainDecorator> TerrainDecoratorPtr;
public:
	TerrainGenPipeline(const DensityGeneratorPtr& densityGenerator,
		                const TerrainComposerPtr& terrainComposer);
	~TerrainGenPipeline() = default;
public:
	void addDecorator(const TerrainDecoratorPtr& decorator);

	std::shared_ptr<Chunk> generateChunk(World& world, const Vector3& position) override;
private:
	DensityGeneratorPtr m_densityGenerator;
	TerrainComposerPtr m_terrainComposer;
	std::vector<TerrainDecoratorPtr> m_terrainDecorators;
};