#pragma once

class ChunkMesh;
struct Vector3;
class World;

class IMeshGenerator {
public:
	virtual void generateMesh(ChunkMesh& mesh, const World& world, const Vector3& blockPosition) = 0;
};