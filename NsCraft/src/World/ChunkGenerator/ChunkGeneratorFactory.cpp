#include "ChunkGeneratorFactory.h"
#include "VoidChunkGenerator.h"

std::unique_ptr<IChunkGenerator> ChunkGeneratorFactory::createChunkGenerator(const ChunkGeneratorType& type) const {
	std::unique_ptr<IChunkGenerator> chunkGenerator;

	switch (type) {
	case ChunkGeneratorType::VOID:
		chunkGenerator = std::make_unique<VoidChunkGenerator>();
		break;
	default:
		chunkGenerator = std::make_unique<VoidChunkGenerator>();
		break;
	}

	return chunkGenerator;
}
