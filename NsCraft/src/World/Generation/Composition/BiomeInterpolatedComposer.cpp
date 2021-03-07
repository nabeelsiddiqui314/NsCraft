#include "BiomeInterpolatedComposer.h"
#include "../../Chunk/Chunk.h"
#include "../Shape/ChunkShape.h"
#include "../../../Math/Vector3.h"
#include "../../../Math/Vector2.h"
#include "../Biome/BiomeMap.h"
#include "../Biome/Biome.h"
#include "../Biome/BiomeRegistry.h"

void BiomeInterpolatedComposer::compose(const Vector3& position, Chunk& chunk, const ChunkShape& shape, const BiomeMap& biomeMap) {
	auto& biomeRegistry = BiomeRegistry::getInstance();

	for (int x = 0; x < Chunk::WIDTH; x++) {
		for (int z = 0; z < Chunk::WIDTH; z++) {
			auto& biome = biomeRegistry.getBiomeFromID(biomeMap.getBiomeAt({ x, z }));

			//todo : interpolation to make the transition natural

			for (int y = 0; y < Chunk::WIDTH; y++) {
				if (shape.getDensity({x, y, z}) == Density::SOLID) {
					auto positionData = shape.getPostionData({x, y, z});
					Block_ID block = biome.getBlockAtDepth(positionData.distanceFromTop);
					chunk.setBlock({x, y, z}, block);
				}
			}
		}
	}
}