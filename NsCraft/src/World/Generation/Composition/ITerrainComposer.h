#pragma once

class Chunk;
class DensityMap;

class ITerrainComposer {
public:
	ITerrainComposer() = default;
	virtual ~ITerrainComposer() = default;
public:
	virtual void compose(Chunk& chunk, const DensityMap& densityMap) = 0;
};