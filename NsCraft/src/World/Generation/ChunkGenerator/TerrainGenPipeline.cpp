#include "TerrainGenPipeline.h"
#include "../../../Math/Vector3.h"
#include "../../../Math/Vector2.h"
#include "../../Chunk/Chunk.h"
#include "../Biome/IBiomeGenerator.h"
#include "../Heightmap/IHeightmapGenerator.h"
#include "../Composition/ITerrainComposer.h"
#include "../Decoration/ITerrainDecorator.h"

TerrainGenPipeline::TerrainGenPipeline(const BiomeGeneratorPtr& biomeGenerator,
                                       const HeightmapGeneratorPtr& heightGenerator,
                                       const TerrainComposerPtr& terrainComposer)
    : m_biomeGenerator(biomeGenerator),
      m_heightGenerator(heightGenerator),
      m_terrainComposer(terrainComposer) {}

void TerrainGenPipeline::addDecorator(const TerrainDecoratorPtr& decorator) {
    m_terrainDecorators.push_back(decorator);
}

std::shared_ptr<Chunk> TerrainGenPipeline::generateChunk(World& world, const Vector3& position) {
    auto chunk = std::make_shared<Chunk>();

    Vector2 position2D = {position.x, position.z};

    auto biomeMap = m_biomeGenerator->generateBiome(position2D);
    auto heightmap = m_heightGenerator->generateHeightmap(position2D, *biomeMap);

    m_terrainComposer->compose(position, *chunk, *heightmap, *biomeMap);

    for (auto& terrainDecorator : m_terrainDecorators) {
        terrainDecorator->decorate(position, *chunk, *heightmap, world);
    }

    return chunk;
}
