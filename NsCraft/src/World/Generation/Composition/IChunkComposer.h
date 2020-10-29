#pragma once

class Chunk;
class DensityMap;

class IChunkComposer {
public:
	IChunkComposer() = default;
	virtual ~IChunkComposer() = default;
public:
	virtual void composeChunk(Chunk& chunk, const DensityMap& densityMap) = 0;
};