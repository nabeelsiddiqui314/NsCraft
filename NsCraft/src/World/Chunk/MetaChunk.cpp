#include "MetaChunk.h"
#include "Chunk.h"

void MetaChunk::modifyBlock(const Vector3& blockPosition, Block_ID id) {
	m_modifiedBlocks[blockPosition] = id;
}

void MetaChunk::applyModification(Chunk& chunk) const {
	for (auto& [blockPosition, blockID] : m_modifiedBlocks) {
		chunk.setBlock(blockPosition, blockID);
	}
}
