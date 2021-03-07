#pragma once
#include "ITerrainComposer.h"

class BiomeInterpolatedComposer : public ITerrainComposer {
public:
	BiomeInterpolatedComposer() = default;
	~BiomeInterpolatedComposer() = default;
public:
	void compose(const Vector3& position, Chunk& chunk, const ChunkShape& shape, const BiomeMap& biomeMap) override;
};