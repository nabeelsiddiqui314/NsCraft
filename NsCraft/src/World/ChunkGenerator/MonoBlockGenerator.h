#pragma once
#include "IChunkGenerator.h"
#include "../Blocks/BlockDefs.h"

class MonoBlockGenerator : public IChunkGenerator {
public:
	MonoBlockGenerator();
	MonoBlockGenerator(Block_ID blockID);
	~MonoBlockGenerator() = default;
public:
	std::shared_ptr<Chunk> generateChunk(const Vector3& position) override;
private:
	const Block_ID m_blockID;
};