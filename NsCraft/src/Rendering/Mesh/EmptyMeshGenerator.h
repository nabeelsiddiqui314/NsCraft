#pragma once
#include "IMeshGenerator.h"

class EmptyMeshGenerator : public IMeshGenerator {
public:
	EmptyMeshGenerator() = default;
	~EmptyMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const Neighborhood& neighborhood) override {}
};