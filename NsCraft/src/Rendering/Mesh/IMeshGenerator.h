#pragma once
#include "../../World/Chunk/ChunkNode.h"

class ChunkMesh;
struct Vector3;
class World;

struct Neighborhood {
	ChunkNode centre;
	ChunkNode left;
	ChunkNode right;
	ChunkNode top;
	ChunkNode bottom;
	ChunkNode front;
	ChunkNode back;
};

class IMeshGenerator {
public:
	virtual void generateMesh(ChunkMesh& mesh, const Neighborhood& neighborhood) = 0;
};