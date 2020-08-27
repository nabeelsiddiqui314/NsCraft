#include "Chunk.h"
#include "../../Math/Vector3.h"

Chunk::Chunk() {
	m_blocks.fill(0);
}

Chunk::Chunk(Block_ID blockID) {
	m_blocks.fill(blockID);
}

void Chunk::setBlock(const Vector3& position, Block_ID id) {
	m_blocks[getIndex(position)] = id;
}

Block_ID Chunk::getBlock(const Vector3& position) const {
	return m_blocks[getIndex(position)];
}

std::size_t Chunk::getIndex(const Vector3& position) const {
	return position.x + WIDTH * (position.y + WIDTH * position.z);
}
