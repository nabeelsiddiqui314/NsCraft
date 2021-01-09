#pragma once
#include <memory>
#include <string>
#include "IMeshGenerator.h"

class CubeMeshGenerator : public IMeshGenerator {
public:
	CubeMeshGenerator(const std::string& topTexture, const std::string& sideTexture, const std::string& bottomTexture);
	~CubeMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const World& world, const Vector3& chunkPosition, const Vector3& blockPosition) override;
private:
	std::string m_topTexture;
	std::string m_sideTexture;
	std::string m_bottomTexture;
};