#include "RandomBlockGenerator.h"
#include "../Chunk/Chunk.h"
#include "../../Math/Vector3.h"
#include <ctime>

RandomBlockGenerator::RandomBlockGenerator(const std::vector<Block_ID>& blockList) 
	: m_blockList(blockList) {
	srand(time(NULL));
}

std::shared_ptr<Chunk> RandomBlockGenerator::generateChunk(const Vector3& position) {
	auto chunk = std::make_shared<Chunk>();
	for (int x = 0; x < Chunk::WIDTH; x++) {
		for (int y = 0; y < Chunk::WIDTH; y++) {
			for (int z = 0; z < Chunk::WIDTH; z++) {
				std::size_t randomIndex = rand() % m_blockList.size();
				Block_ID randomBlock = m_blockList[randomIndex];

				chunk->setBlock({x, y, z}, randomBlock);
			}
		}
	}

	return chunk;
}
