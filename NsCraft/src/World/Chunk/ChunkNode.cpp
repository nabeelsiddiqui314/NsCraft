#include "ChunkNode.h"

ChunkNode::ChunkNode() 
	: ChunkNode(0) {}

ChunkNode::ChunkNode(Block_ID blockID)
	: m_blockId(blockID) {}

void ChunkNode::setBlockID(Block_ID blockID) {
	m_blockId = blockID;
}

Block_ID ChunkNode::getBlockID() const {
	return m_blockId;
}

void ChunkNode::setSkyLight(std::uint8_t value) {
	m_lightNode.setSkyLight(value);
}

void ChunkNode::setNaturalLight(std::uint8_t value) {
	m_lightNode.setNaturalLight(value);
}

std::uint8_t ChunkNode::getSkyLight() const {
	return m_lightNode.getSkyLight();
}

std::uint8_t ChunkNode::getNaturalLight() const {
	return m_lightNode.getNaturalLight();
}
