#include "TerrainGenPipeline.h"
#include "../../../Math/Vector3.h"
#include "../../Chunk/Chunk.h"
#include "../Density/IDensityGenerator.h"
#include "../Composition/IChunkComposer.h"

std::shared_ptr<Chunk> TerrainGenPipeline::generateChunk(World& world, const Vector3& position) {
    auto chunk = std::make_shared<Chunk>();

    auto densityMap = m_densityGenerator->generateDensityMap(position);
    
    m_chunkComposer->composeChunk(*chunk, *densityMap);

    return chunk;
}
