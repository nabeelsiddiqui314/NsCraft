#pragma once
#include "IMeshGenerator.h"
#include <GL/glew.h>

class LiquidMeshGenerator : public IMeshGenerator {
public:
	LiquidMeshGenerator(GLuint texture);
	~LiquidMeshGenerator() = default;
public:
	void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) override;
private:
	GLuint m_texture;
};