#pragma once
#include "../../../Utilities/Flat2DArray.h"
#include "BiomeDefs.h"
#include "../../Chunk/Chunk.h"

struct Vector2;

class BiomeMap {
public:
	BiomeMap() = default;
	~BiomeMap() = default;
public:
	void setBiomeAt(const Vector2& position, Biome_ID biome);
	Biome_ID getBiomeAt(const Vector2& position) const;
private:
	Flat2DArray<Biome_ID, Chunk::WIDTH, Chunk::WIDTH> m_biomeMap;
};