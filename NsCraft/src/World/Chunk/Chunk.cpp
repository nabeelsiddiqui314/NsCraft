#include "Chunk.h"
#include "../../Math/Vector3.h"
#include "../Blocks/BlockRegistry.h"
#include "../Blocks/Block.h"

Chunk::Chunk() : Chunk(0) {}

Chunk::Chunk(Block_ID blockID) : m_opaqueBlockCount(0) {
	m_nodes.fill(blockID);

	auto& blockRegistry = BlockRegistry::getInstance();
	auto& block = blockRegistry.getBlockFromID(blockID);

	if (block.isInvisible()) {
		m_invisibleBlockCount = WIDTH * WIDTH * WIDTH;
	}
	if (block.isCompletelyOpaque()) {
		m_opaqueBlockCount = WIDTH * WIDTH * WIDTH;
	}
}

void Chunk::setBlock(const Vector3& position, Block_ID blockID) {
	std::size_t index = getIndex(position);
	Block_ID previousBlockID = m_nodes[index].getBlockID();

	if (previousBlockID != blockID) {
		m_nodes[index].setBlockID(blockID);

		auto& blockRegistry = BlockRegistry::getInstance();

		auto& previousBlock = blockRegistry.getBlockFromID(previousBlockID);
		auto& block = blockRegistry.getBlockFromID(blockID);


		if (previousBlock.isInvisible() && !block.isInvisible()) {
			m_invisibleBlockCount--;
		}
		else if (!previousBlock.isInvisible() && block.isInvisible()) {
			m_invisibleBlockCount++;
		}

		if (previousBlock.isCompletelyOpaque() && !block.isCompletelyOpaque()) {
			m_opaqueBlockCount--;
		}
		else if (!previousBlock.isCompletelyOpaque() && block.isCompletelyOpaque()) {
			m_opaqueBlockCount++;
		}
	}
}

Block_ID Chunk::getBlock(const Vector3& position) const {
	return m_nodes[getIndex(position)].getBlockID();
}

void Chunk::setSkyLight(const Vector3& position, std::uint8_t value) {
	m_nodes[getIndex(position)].setSkyLight(value);
}

void Chunk::setNaturalLight(const Vector3& position, std::uint8_t value) {
	m_nodes[getIndex(position)].setNaturalLight(value);
}

std::uint8_t Chunk::getSkyLight(const Vector3& position) const {
	return m_nodes[getIndex(position)].getSkyLight();
}

std::uint8_t Chunk::getNaturalLight(const Vector3& position) const {
	return m_nodes[getIndex(position)].getNaturalLight();
}

ChunkNode Chunk::getNode(const Vector3& position) const {
	return m_nodes[getIndex(position)];
}


bool Chunk::isFullyInvisible() const {
	return m_invisibleBlockCount == WIDTH * WIDTH * WIDTH;
}

bool Chunk::isFullyOpaque() const {
	return m_opaqueBlockCount == WIDTH * WIDTH * WIDTH;
}

std::size_t Chunk::getIndex(const Vector3& position) const {
	return position.x + WIDTH * (position.y + WIDTH * position.z);
}