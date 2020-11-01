#pragma once
#include "ITerrainComposer.h"

class DefaultComposer : public ITerrainComposer {
public:
	DefaultComposer() = default;
	~DefaultComposer() = default;
public:
	void compose(Chunk& chunk, const ChunkShape& shape) override;
};