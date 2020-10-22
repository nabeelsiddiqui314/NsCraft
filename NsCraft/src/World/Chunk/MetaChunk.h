#pragma once
#include <unordered_map>
#include "../../Math/Vector3.h"
#include "../Blocks/BlockDefs.h"

class Chunk;

class MetaChunk {
public:
	void modifyBlock(const Vector3& blockPosition, Block_ID id);
	void applyModification(const std::shared_ptr<Chunk>& chunk);
private:
	std::unordered_map<Vector3, Block_ID> m_modifiedBlocks;
};