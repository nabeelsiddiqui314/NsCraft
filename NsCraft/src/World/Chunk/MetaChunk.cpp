#include "MetaChunk.h"
#include "Chunk.h"

void MetaChunk::modifyBlock(const Vector3& blockPosition, Block_ID id) {
	m_modifiedBlocks[blockPosition] = id;
}

void MetaChunk::applyModification(const std::shared_ptr<Chunk>& chunk) {
	for (auto& [blockPosition, blockID] : m_modifiedBlocks) {
		chunk->setBlock(blockPosition, blockID);
	}

	m_modifiedBlocks.clear();
}
