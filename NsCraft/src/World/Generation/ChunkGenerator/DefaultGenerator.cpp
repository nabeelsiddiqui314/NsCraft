#include "DefaultGenerator.h"
#include "../../../Math/Vector3.h"

DefaultGenerator::DefaultGenerator() : m_heightMap(31415, {5, 200, 150, 5, 4}) {}

std::shared_ptr<Chunk> DefaultGenerator::generateChunk(const Vector3& position) {
	auto chunk = std::make_shared<Chunk>();

	for (int x = 0; x < Chunk::WIDTH; x++) {
		for (int z = 0; z < Chunk::WIDTH; z++) {
			int chunkHeight = Chunk::WIDTH;
			int height = m_heightMap.getHeightAt({ position.x, position.z }, { x, z });



			if (height > position.y * Chunk::WIDTH &&
				height < (position.y + 1) * Chunk::WIDTH) {
				chunkHeight = height % Chunk::WIDTH;
			}

			if (height == position.y * Chunk::WIDTH) {
				chunkHeight = 0;
			}

			if (height < position.y * Chunk::WIDTH) {
				chunkHeight = 0;
			}

			for (int y = 0; y < chunkHeight; y++) {
				chunk->setBlock({ x , y, z }, 1);
			}
		}
	}

	return chunk;
}