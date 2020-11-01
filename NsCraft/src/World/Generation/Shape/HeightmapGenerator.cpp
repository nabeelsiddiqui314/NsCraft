#include "HeightmapGenerator.h"
#include "../../Chunk/Chunk.h"
#include "../../../Math/Vector3.h"
#include "ChunkShape.h"

HeightmapGenerator::HeightmapGenerator(std::uint32_t seed, const NoiseProperties& noiseProperties) 
 : m_heightmap(seed, noiseProperties) {}

ChunkShapePtr HeightmapGenerator::generateShape(const Vector3& position) {
	ChunkShapePtr shape = std::shared_ptr<ChunkShape>();

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
				shape->setDensity({ x, y, z }, Density::SOLID);
				
				PositionData data;

				if (height == Chunk::WIDTH * position.y + y) {
					data.positionType = PositionType::SURFACE;
					data.distanceFromTop = 0;
				}
				else if (position.y == 0 && y == 0) {
					data.positionType = PositionType::BASE;
					data.distanceFromTop = height;
				}
				else {
					data.positionType = PositionType::INTERIOR;
					data.distanceFromTop = height - position.y + Chunk::WIDTH + y;
				}

				shape->setPositionData({x, y, z}, data);
			}
		}
	}

	return shape;
}