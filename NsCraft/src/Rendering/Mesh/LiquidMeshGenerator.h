#pragma once
#include "IMeshGenerator.h"
#include <GL/glew.h>

class LiquidMeshGenerator : public IMeshGenerator {
public:
	LiquidMeshGenerator(GLuint texture);
	~LiquidMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const Neighborhood& neighborhood) override;
private:
	GLuint m_texture;
};