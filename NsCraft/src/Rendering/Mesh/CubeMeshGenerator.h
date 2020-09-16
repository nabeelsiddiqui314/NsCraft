#pragma once
#include "IMeshGenerator.h"
#include <memory>

class BlockRegistry;

class CubeMeshGenerator : public IMeshGenerator {
public:
	CubeMeshGenerator(const BlockRegistry& blockRegistry);
	~CubeMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const World& world, const Vector3& blockPosition) override;
private:
	const BlockRegistry& m_blockRegistry;
};