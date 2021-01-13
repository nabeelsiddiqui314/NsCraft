#pragma once
#include "../Blocks/BlockDefs.h"
#include "../../Lighting/LightNode.h"

struct Vector3;

class ChunkNode {
public:
	ChunkNode();
	ChunkNode(Block_ID blockID);
public:
	void setBlockID(Block_ID blockID);
	Block_ID getBlockID() const;

	void setSkyLight(std::uint8_t value);
	void setNaturalLight(std::uint8_t value);

	std::uint8_t getSkyLight() const;
	std::uint8_t getNaturalLight() const;
private:
	Block_ID m_blockId;
	LightNode m_lightNode;
};