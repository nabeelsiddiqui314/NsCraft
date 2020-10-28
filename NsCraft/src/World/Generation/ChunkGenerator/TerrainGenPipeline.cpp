#include "TerrainGenPipeline.h"
#include "../../../Math/Vector3.h"
#include "../../Chunk/Chunk.h"

std::shared_ptr<Chunk> TerrainGenPipeline::generateChunk(World& world, const Vector3& position) {
    auto chunk = std::make_shared<Chunk>();

    return chunk;
}
