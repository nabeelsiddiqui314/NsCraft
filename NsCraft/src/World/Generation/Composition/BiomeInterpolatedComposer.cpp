#include "BiomeInterpolatedComposer.h"
#include "../../Chunk/Chunk.h"
#include "../Heightmap/Heightmap.h"
#include "../../../Math/Vector3.h"
#include "../../../Math/Vector2.h"
#include "../Biome/BiomeMap.h"
#include "../Biome/Biome.h"
#include "../Biome/BiomeRegistry.h"
#include "../../Blocks/BlockRegistry.h"

void BiomeInterpolatedComposer::compose(const Vector3& position, Chunk& chunk, const Heightmap& heightmap, const BiomeMap& biomeMap) {
	auto& biomeRegistry = BiomeRegistry::getInstance();
	auto& blockRegistry = BlockRegistry::getInstance();

	for (int x = 0; x < Chunk::WIDTH; x++) {
		for (int z = 0; z < Chunk::WIDTH; z++) {
			auto& biome = biomeRegistry.getBiomeFromID(biomeMap.getBiomeAt({ x, z }));

			//todo : interpolation to make the transition natural

			int height = heightmap.getHeightAt({x, z});

			for (int y = 0; y < Chunk::WIDTH; y++) {
				int yWorld = y + position.y * Chunk::WIDTH;

				if (yWorld <= height) {
					Block_ID block = biome.getBlockAtDepth(height - yWorld);
					chunk.setBlock({x, y, z}, block);
				}
				else {
					if (y + position.y * Chunk::WIDTH < 30) {
						chunk.setBlock({x, y, z}, blockRegistry.getBlockIDFromName("water"));
					}
				}
			}
		}
	}
}