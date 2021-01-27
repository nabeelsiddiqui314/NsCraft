#pragma once
#include <memory>
#include <string>
#include <GL/glew.h>
#include "IMeshGenerator.h"

class CubeMeshGenerator : public IMeshGenerator {
public:
	CubeMeshGenerator(GLuint topTexture, GLuint sideTexture, GLuint bottomTexture);
	~CubeMeshGenerator() = default;
public:
	void generateMesh(ChunkMesh& mesh, const Neighborhood& neighborhood) override;
private:
	GLuint m_topTexture;
	GLuint m_sideTexture;
	GLuint m_bottomTexture;
};