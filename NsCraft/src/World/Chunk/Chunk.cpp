#include "Chunk.h"
#include "../../Math/Vector3.h"
#include "../Blocks/BlockRegistry.h"
#include "../Blocks/Block.h"

Chunk::Chunk() : Chunk(0) {}

Chunk::Chunk(Block_ID blockID) : m_opaqueBlockCount(0) {
	m_blocks.fill(blockID);
	m_lightMap.fill(0);

	auto& blockRegistry = BlockRegistry::getInstance();
	auto& block = blockRegistry.getBlockFromID(blockID);

	if (block.isOpaque()) {
		m_opaqueBlockCount = WIDTH * WIDTH * WIDTH;
	}
}

void Chunk::setBlock(const Vector3& position, Block_ID blockID) {
	std::size_t index = getIndex(position);
	Block_ID previousBlockID = m_blocks[index];

	if (previousBlockID != blockID) {
		m_blocks[index] = blockID;

		auto& blockRegistry = BlockRegistry::getInstance();

		auto& previousBlock = blockRegistry.getBlockFromID(previousBlockID);
		auto& block = blockRegistry.getBlockFromID(blockID);

		if (previousBlock.isOpaque() && ~block.isOpaque()) {
			m_opaqueBlockCount--;
		}
		else if (~previousBlock.isOpaque() && block.isOpaque()) {
			m_opaqueBlockCount++;
		}
	}
}

Block_ID Chunk::getBlock(const Vector3& position) const {
	return m_blocks[getIndex(position)];
}

void Chunk::setNaturalLight(const Vector3& position, std::uint8_t value) {
	m_lightMap[getIndex(position)] = (m_lightMap[getIndex(position)] & 0xF0) | value;
}

void Chunk::setSkyLight(const Vector3& position, std::uint8_t value) {
	m_lightMap[getIndex(position)] = (m_lightMap[getIndex(position)] & 0xF) | (value << 4);
}

std::uint8_t Chunk::getNaturalLight(const Vector3& position) const {
	return m_lightMap[getIndex(position)] & 0xF;
}

std::uint8_t Chunk::getSkyLight(const Vector3& position) const {
	return (m_lightMap[getIndex(position)] >> 4) & 0xF;
}

bool Chunk::isFullyOpaque() const {
	return m_opaqueBlockCount == WIDTH * WIDTH * WIDTH;
}

std::size_t Chunk::getIndex(const Vector3& position) const {
	return position.x + WIDTH * (position.y + WIDTH * position.z);
}
