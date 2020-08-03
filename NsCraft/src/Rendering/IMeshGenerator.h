#pragma once

class ChunkMesh;
struct Vector3;

class IMeshGenerator {
public:
	virtual void generateMesh(ChunkMesh& mesh, const Vector3& blockPosition) = 0;
};