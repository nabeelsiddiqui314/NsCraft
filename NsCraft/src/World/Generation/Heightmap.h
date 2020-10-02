#pragma once
#include <unordered_map>
#include <array>
#include "../../Math/Vector2.h"
#include "../Chunk/Chunk.h"
#include "../../Math/Noise.h"

class Heightmap {
private:
	typedef std::array<int, Chunk::WIDTH * Chunk::WIDTH> ChunkHeightmap;
public:
	Heightmap(std::uint32_t seed, const NoiseProperties& noiseProperties);
	~Heightmap() = default;
public:
	int getHeightAt(const Vector2& chunkPosition, const Vector2& blockPosition);
private:
	std::size_t getIndex(const Vector2& blockPosition) const;
private:
	std::unordered_map<Vector2, ChunkHeightmap> m_chunkHeightmaps;
	Noise m_noise;
};