#include "TerrainGenPipeline.h"
#include "../../../Math/Vector3.h"
#include "../../../Math/Vector2.h"
#include "../../Chunk/Chunk.h"
#include "../Biome/IBiomeGenerator.h"
#include "../Shape/IShapeGenerator.h"
#include "../Composition/ITerrainComposer.h"
#include "../Decoration/ITerrainDecorator.h"

TerrainGenPipeline::TerrainGenPipeline(const BiomeGeneratorPtr& biomeGenerator,
                                       const ShapeGeneratorPtr& shapeGenerator,
                                       const TerrainComposerPtr& terrainComposer)
    : m_biomeGenerator(biomeGenerator),
      m_shapeGenerator(shapeGenerator),
      m_terrainComposer(terrainComposer) {}

void TerrainGenPipeline::addDecorator(const TerrainDecoratorPtr& decorator) {
    m_terrainDecorators.push_back(decorator);
}

std::shared_ptr<Chunk> TerrainGenPipeline::generateChunk(World& world, const Vector3& position) {
    auto chunk = std::make_shared<Chunk>();

    auto biomeMap = m_biomeGenerator->generateBiome({position.x, position.z});

    auto chunkShape = m_shapeGenerator->generateShape(position, *biomeMap);
    m_terrainComposer->compose(position, *chunk, *chunkShape, *biomeMap);

    for (auto& terrainDecorator : m_terrainDecorators) {
        terrainDecorator->decorate(position, *chunk, *chunkShape, world);
    }

    return chunk;
}
