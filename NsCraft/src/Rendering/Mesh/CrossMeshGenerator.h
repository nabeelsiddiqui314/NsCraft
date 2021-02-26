#pragma once
#include "IMeshGenerator.h"
#include <GL/glew.h>

class CrossMeshGenerator : public IMeshGenerator {
public:
	CrossMeshGenerator(GLuint texture);
	~CrossMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const Neighborhood& neighborhood) override;
private:
	GLuint m_texture;
};