#include "Heightmap.h"

Heightmap::Heightmap(std::uint32_t seed, const NoiseProperties& noiseProperties) 
	: m_noise(seed, noiseProperties) {}

int Heightmap::getHeightAt(const Vector2& chunkPosition, const Vector2& blockPosition) {
	if (m_chunkHeightmaps.find(chunkPosition) == m_chunkHeightmaps.end()) {
		ChunkHeightmap chunkHeightmap;
		chunkHeightmap.fill(0);

		for (int x = 0; x < Chunk::WIDTH; x++) {
			for (int z = 0; z < Chunk::WIDTH; z++) {
				chunkHeightmap[getIndex({ x, z })] = m_noise.getNoiseAt(Vector2(x, z) + chunkPosition * Chunk::WIDTH);
			}
		}
		m_chunkHeightmaps.emplace(std::make_pair(chunkPosition, chunkHeightmap));
	} 
	
	return m_chunkHeightmaps.at(chunkPosition)[getIndex(blockPosition)];
}

std::size_t Heightmap::getIndex(const Vector2& blockPosition) const {
	return blockPosition.x + blockPosition.y * Chunk::WIDTH;
}