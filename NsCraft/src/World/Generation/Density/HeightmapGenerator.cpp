#include "HeightmapGenerator.h"
#include "../../Chunk/Chunk.h"
#include "../../../Math/Vector3.h"
#include "DensityMap.h"

HeightmapGenerator::HeightmapGenerator(std::uint32_t seed, const NoiseProperties& noiseProperties) 
 : m_heightmap(seed, noiseProperties) {}

DensityMapPtr HeightmapGenerator::generateDensityMap(const Vector3& position) {
    DensityMapPtr densityMap = std::shared_ptr<DensityMap>();

	for (int x = 0; x < Chunk::WIDTH; x++) {
		for (int z = 0; z < Chunk::WIDTH; z++) {
			int chunkHeight = Chunk::WIDTH;
			int height = m_heightmap.getHeightAt({ position.x, position.z }, { x, z });

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
				densityMap->setDensity({ x, y, z }, Density::SOLID);
			}
		}
	}

    return densityMap;
}
