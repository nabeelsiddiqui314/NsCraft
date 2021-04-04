#pragma once

class ChunkMesh;
struct Vector3;
class PaddedChunk;

class IMeshGenerator {
public:
	virtual void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) = 0;
};