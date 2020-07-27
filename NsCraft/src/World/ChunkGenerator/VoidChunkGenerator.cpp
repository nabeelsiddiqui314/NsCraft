#include "VoidChunkGenerator.h"
#include "../Chunk/Chunk.h"

std::shared_ptr<Chunk> VoidChunkGenerator::generateChunk(const Vector3& position) {
	return std::make_shared<Chunk>();
}
