#pragma once
#include "IMeshGenerator.h"
#include <memory>

class CubeMeshGenerator : public IMeshGenerator {
public:
	CubeMeshGenerator() = default;
	~CubeMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const BlockRegistry& blockRegistry, const World& world, const Vector3& blockPosition) override;
};