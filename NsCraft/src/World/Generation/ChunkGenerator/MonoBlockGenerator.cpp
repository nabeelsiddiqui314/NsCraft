#include "MonoBlockGenerator.h"
#include "../../Chunk/Chunk.h"

MonoBlockGenerator::MonoBlockGenerator() 
	: m_blockID(0) {}

MonoBlockGenerator::MonoBlockGenerator(Block_ID blockID)
	: m_blockID(blockID) {}

std::shared_ptr<Chunk> MonoBlockGenerator::generateChunk(World& world, const Vector3& position) {
	return std::make_shared<Chunk>(m_blockID);
}
