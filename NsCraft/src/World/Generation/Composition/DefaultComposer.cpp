#include "DefaultComposer.h"
#include "../../Chunk/Chunk.h"
#include "../Shape/ChunkShape.h"
#include "../../../Math/Vector3.h"
#include "../../Blocks/BlockRegistry.h"

void DefaultComposer::compose(Chunk& chunk, const ChunkShape& shape) {
	auto& blockRegistry = BlockRegistry::getInstance();

	Block_ID grass = blockRegistry.getBlockIDFromName("grass");
	Block_ID dirt = blockRegistry.getBlockIDFromName("dirt");
	Block_ID bedrock = blockRegistry.getBlockIDFromName("bedrock");

	for (int x = 0; x < Chunk::WIDTH; x++) {
		for (int y = 0; y < Chunk::WIDTH; y++) {
			for (int z = 0; z < Chunk::WIDTH; z++) {
				if (shape.getDensity({x, y, z}) == Density::SOLID) {
					auto positionData = shape.getPostionData({x, y, z});

					switch (positionData.positionType) {
					case PositionType::SURFACE:
						chunk.setBlock({x, y, z}, grass);
						break;
					case PositionType::INTERIOR:
						chunk.setBlock({ x, y, z }, dirt);
						break;
					case PositionType::BASE:
						chunk.setBlock({ x, y, z }, bedrock);
						break;
					}
				}
			}
		}
	}
}