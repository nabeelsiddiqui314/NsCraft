#include "TerrainGenPipeline.h"
#include "../../../Math/Vector3.h"
#include "../../Chunk/Chunk.h"
#include "../Density/IDensityGenerator.h"
#include "../Composition/ITerrainComposer.h"
#include "../Decoration/ITerrainDecorator.h"

std::shared_ptr<Chunk> TerrainGenPipeline::generateChunk(World& world, const Vector3& position) {
    auto chunk = std::make_shared<Chunk>();

    auto densityMap = m_densityGenerator->generateDensityMap(position);
    m_terrainComposer->compose(*chunk, *densityMap);

    for (auto& terrainDecorator : m_terrainDecorators) {
        terrainDecorator->decorate(position, *chunk, world);
    }

    return chunk;
}
