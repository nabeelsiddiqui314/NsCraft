#include "PaddedChunk.h"
#include "../../Math/Vector3.h"

PaddedChunk::PaddedChunk(const ChunkNeighborhood& neighborhood) 
	: m_neighborhood(neighborhood) {
    
}

ChunkNode PaddedChunk::getNode(const Vector3& position) const {
	auto [chunk, blockPosition] = getBlockLocation(position);

    if (!chunk) {
        return ChunkNode();
    }

	return chunk->getNode(blockPosition);
}

std::pair<ChunkPtr, Vector3> PaddedChunk::getBlockLocation(const Vector3& position) const {
    ChunkPtr chunk = m_neighborhood.centre;
    Vector3 newBlockPosition = position;

    if (position.x < 0) {
        newBlockPosition.x = Chunk::WIDTH - abs(newBlockPosition.x);
        chunk = m_neighborhood.left;
    }
    else if (position.x >= Chunk::WIDTH) {
        newBlockPosition.x = newBlockPosition.x % Chunk::WIDTH;
        chunk = m_neighborhood.right;
    }

    else if (position.y < 0) {
        newBlockPosition.y = Chunk::WIDTH - abs(newBlockPosition.y);
        chunk = m_neighborhood.bottom;
    }
    else if (position.y >= Chunk::WIDTH) {
        newBlockPosition.y = newBlockPosition.y % Chunk::WIDTH;
        chunk = m_neighborhood.top;
    }

    else if (position.z < 0) {
        newBlockPosition.z = Chunk::WIDTH - abs(newBlockPosition.z);
        chunk = m_neighborhood.back;
    }

    else if (position.z >= Chunk::WIDTH) {
        newBlockPosition.z = newBlockPosition.z % Chunk::WIDTH;
        chunk = m_neighborhood.front;
    }

    return {chunk, newBlockPosition};
}
