#pragma once
#include "IChunkGenerator.h"
#include <memory>
#include <vector>

class IBiomeGenerator;
class IHeightmapGenerator;
class ITerrainComposer;
class ITerrainDecorator;

class TerrainGenPipeline : public IChunkGenerator {
private:
	typedef std::shared_ptr<IBiomeGenerator> BiomeGeneratorPtr;
	typedef std::shared_ptr<IHeightmapGenerator> HeightmapGeneratorPtr;
	typedef std::shared_ptr<ITerrainComposer> TerrainComposerPtr;
	typedef std::shared_ptr<ITerrainDecorator> TerrainDecoratorPtr;
public:
	TerrainGenPipeline(const BiomeGeneratorPtr& biomeGenerator,
		               const HeightmapGeneratorPtr& heightGenerator,
		               const TerrainComposerPtr& terrainComposer);
	~TerrainGenPipeline() = default;
public:
	void addDecorator(const TerrainDecoratorPtr& decorator);

	std::shared_ptr<Chunk> generateChunk(World& world, const Vector3& position) override;
private:
	BiomeGeneratorPtr m_biomeGenerator;
	HeightmapGeneratorPtr m_heightGenerator;
	TerrainComposerPtr m_terrainComposer;
	std::vector<TerrainDecoratorPtr> m_terrainDecorators;
};