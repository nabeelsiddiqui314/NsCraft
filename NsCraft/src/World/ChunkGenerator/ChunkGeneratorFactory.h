#pragma once
#include <memory>
#include "ChunkGeneratorType.h"

class IChunkGenerator;

class ChunkGeneratorFactory {
public:
	ChunkGeneratorFactory() = default;
	~ChunkGeneratorFactory() = default;
public:
	std::unique_ptr<IChunkGenerator> createChunkGenerator(const ChunkGeneratorType& type) const;
};