#pragma once

class ChunkMesh;
struct Vector3;
class PaddedChunk;

class IBlockModel {
public:
	virtual void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) = 0;
};