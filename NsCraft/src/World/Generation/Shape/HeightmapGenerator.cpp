#include "HeightmapGenerator.h"
#include "../../Chunk/Chunk.h"
#include "../../../Math/Vector3.h"
#include "ChunkShape.h"

HeightmapGenerator::HeightmapGenerator(std::uint32_t seed, const NoiseProperties& noiseProperties) 
 : m_noise(seed, noiseProperties) {}

ChunkShapePtr HeightmapGenerator::generateShape(const Vector3& position) {
	ChunkShapePtr shape = std::make_shared<ChunkShape>();

	Vector2 position2d = { position.x, position.z };

	if (!m_heightmap.doesHeightMapExist(position2d)) {
		for (int x = 0; x < Chunk::WIDTH; x++) {
			for (int z = 0; z < Chunk::WIDTH; z++) {
				m_heightmap.setHeightAt(position2d, { x, z }, m_noise.getNoiseAt(position2d * Vector2(Chunk::WIDTH, Chunk::WIDTH) + Vector2(x, z)));
			}
		}
	}

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

				if (height == Chunk::WIDTH * position.y + y + 1) {
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