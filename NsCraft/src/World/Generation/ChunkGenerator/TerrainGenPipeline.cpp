#include "TerrainGenPipeline.h"
#include "../../../Math/Vector3.h"
#include "../../Chunk/Chunk.h"
#include "../Density/IDensityGenerator.h"

std::shared_ptr<Chunk> TerrainGenPipeline::generateChunk(World& world, const Vector3& position) {
    auto chunk = std::make_shared<Chunk>();

    auto densityMap = m_densityGenerator->generateDensity(position);

    return chunk;
}
