#pragma once
#include "IChunkGenerator.h"
#include <vector>
#include "../../Blocks/BlockDefs.h"

class RandomBlockGenerator : public IChunkGenerator {
public:
	RandomBlockGenerator(const std::vector<Block_ID>& blockList);
	~RandomBlockGenerator() = default;
public:
	std::shared_ptr<Chunk> generateChunk(World& world, const Vector3& position) override;
private:
	const std::vector<Block_ID> m_blockList;
};