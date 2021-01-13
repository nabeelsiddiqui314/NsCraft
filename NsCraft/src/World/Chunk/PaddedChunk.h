#pragma once
#include <memory>
#include "Chunk.h"

struct Vector3;

typedef std::shared_ptr<Chunk> ChunkPtr;

struct ChunkNeighborhood {
	ChunkPtr centre;
	ChunkPtr top;
	ChunkPtr bottom;
	ChunkPtr left;
	ChunkPtr right;
	ChunkPtr front;
	ChunkPtr back;
};

class PaddedChunk {
public:
	PaddedChunk(const ChunkNeighborhood& neighborhood);
	~PaddedChunk() = default;
public:
	ChunkNode getNode(const Vector3& position) const;
private:
	std::pair<ChunkPtr, Vector3> getBlockLocation(const Vector3& position) const;
private:
	ChunkNeighborhood m_neighborhood;
};