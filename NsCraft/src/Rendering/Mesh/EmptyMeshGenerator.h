#pragma once
#include "IMeshGenerator.h"

class EmptyMeshGenerator : public IMeshGenerator {
public:
	EmptyMeshGenerator() = default;
	~EmptyMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const World& world, const Vector3& blockPosition) override {}
};