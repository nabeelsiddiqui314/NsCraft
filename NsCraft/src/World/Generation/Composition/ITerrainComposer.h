#pragma once

class Chunk;
class ChunkShape;
class BiomeMap;

class ITerrainComposer {
public:
	ITerrainComposer() = default;
	virtual ~ITerrainComposer() = default;
public:
	virtual void compose(Chunk& chunk, const ChunkShape& shape, const BiomeMap& biomeMap) = 0;
};