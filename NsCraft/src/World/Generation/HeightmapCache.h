#pragma once
#include <unordered_map>
#include <array>
#include "../../Math/Vector2.h"
#include "../Chunk/Chunk.h"

class HeightmapCache {
private:
	typedef std::array<int, Chunk::WIDTH * Chunk::WIDTH> ChunkHeightmap;
public:
	HeightmapCache() = default;
	~HeightmapCache() = default;
public:
	void setHeightAt(const Vector2& chunkPosition, const Vector2& blockPosition, int height);
	int getHeightAt(const Vector2& chunkPosition, const Vector2& blockPosition) const;

	bool doesHeightMapExist(const Vector2& position) const;
private:
	std::size_t getIndex(const Vector2& blockPosition) const;
private:
	std::unordered_map<Vector2, ChunkHeightmap> m_heightmapCacheMap;
};