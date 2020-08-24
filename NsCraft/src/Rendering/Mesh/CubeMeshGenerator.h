#pragma once
#include "IMeshGenerator.h"
#include <memory>

class BlockRegistry;

class CubeMeshGenerator : public IMeshGenerator {
public:
	CubeMeshGenerator(const std::shared_ptr<BlockRegistry>& blockRegistry);
	~CubeMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const World& world, const Vector3& blockPosition) override;
private:
	std::shared_ptr<BlockRegistry> m_blockRegistry;
};