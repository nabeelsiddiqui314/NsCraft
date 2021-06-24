#include "PaddedChunk.h"
#include "Chunk.h"
#include "World.h"
#include "../../Math/CoordinateConversion.h"

PaddedChunk::PaddedChunk(const Vector3& chunkPosition, const World& world) {
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                m_neighborhood.emplace(std::make_pair(Vector3(x, y, z), world.getChunk(chunkPosition + Vector3(x, y, z))));
            }
        }
    }
}

ChunkNode PaddedChunk::getNode(const Vector3& position) const {
	auto [chunkPosition, blockPosition] = CoordinateConversion::worldToChunk(position, Chunk::WIDTH);

    auto& chunk = m_neighborhood.at(chunkPosition);

    ChunkNode node;

    if (chunk) {
        node.blockID = chunk->getBlock(blockPosition);
        node.skyLight = chunk->getSkyLight(blockPosition);
        node.naturalLight = chunk->getNaturalLight(blockPosition);
    }

    return node;
}