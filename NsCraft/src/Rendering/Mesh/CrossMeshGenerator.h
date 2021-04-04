#pragma once
#include "IMeshGenerator.h"
#include <GL/glew.h>

class CrossMeshGenerator : public IMeshGenerator {
public:
	CrossMeshGenerator(GLuint texture);
	~CrossMeshGenerator() = default;
public:
	void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) override;
private:
	GLuint m_texture;
};