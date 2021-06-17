#pragma once
#include <memory>
#include <unordered_map>
#include "../../Math/Vector3.h"
#include "../Blocks/BlockDefs.h"

struct Vector3;
class World;
class Chunk;

typedef std::shared_ptr<Chunk> ChunkPtr;

struct ChunkNode {
	Block_ID blockID = 0;
	std::uint8_t skyLight = 0;
	std::uint8_t naturalLight = 0;
};

class PaddedChunk {
public:
	PaddedChunk(const Vector3& chunkPosition, const World& world);
	~PaddedChunk() = default;
public:
	ChunkNode getNode(const Vector3& position) const;
private:
	std::pair<Vector3, Vector3> getBlockLocation(const Vector3& position) const;
private:
	std::unordered_map<Vector3, ChunkPtr> m_neighborhood;
};