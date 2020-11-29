#pragma once
#include <array>
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
	inline std::size_t getIndex(const Vector2& position) const;
private:
	std::array<Biome_ID, Chunk::WIDTH* Chunk::WIDTH> m_biomeMap;
};