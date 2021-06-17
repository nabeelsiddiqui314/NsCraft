#include "PaddedChunk.h"
#include "Chunk.h"
#include "World.h"

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
	auto [chunkPosition, blockPosition] = getBlockLocation(position);

    auto& chunk = m_neighborhood.at(chunkPosition);

    ChunkNode node;

    if (chunk) {
        node.blockID = chunk->getBlock(blockPosition);
        node.skyLight = chunk->getSkyLight(blockPosition);
        node.naturalLight = chunk->getNaturalLight(blockPosition);
    }

    return node;
}

std::pair<Vector3, Vector3> PaddedChunk::getBlockLocation(const Vector3& position) const {
    Vector3 newChunkPosition = {0, 0, 0};
    Vector3 newBlockPosition = position;

    if (position.x < 0) {
        newBlockPosition.x = Chunk::WIDTH - abs(newBlockPosition.x);
        newChunkPosition.x = -1;
    }
    else if (position.x >= Chunk::WIDTH) {
        newBlockPosition.x = newBlockPosition.x % Chunk::WIDTH;
        newChunkPosition.x = 1;
    }

    if (position.y < 0) {
        newBlockPosition.y = Chunk::WIDTH - abs(newBlockPosition.y);
        newChunkPosition.y = -1;
    }
    else if (position.y >= Chunk::WIDTH) {
        newBlockPosition.y = newBlockPosition.y % Chunk::WIDTH;
        newChunkPosition.y = 1;
    }

    if (position.z < 0) {
        newBlockPosition.z = Chunk::WIDTH - abs(newBlockPosition.z);
        newChunkPosition.z = -1;
    }

    else if (position.z >= Chunk::WIDTH) {
        newBlockPosition.z = newBlockPosition.z % Chunk::WIDTH;
        newChunkPosition.z = 1;
    }

    return {newChunkPosition, newBlockPosition};
}
