#pragma once
#include <GL/glew.h>
#include "IMeshGenerator.h"

class CubeMeshGenerator : public IMeshGenerator {
public:
	CubeMeshGenerator(GLuint topTexture, GLuint sideTexture, GLuint bottomTexture);
	~CubeMeshGenerator() = default;
public:
	void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) override;
private:
	float getAmbientOcclusion(bool side1, bool side2, bool corner);
private:
	GLuint m_topTexture;
	GLuint m_sideTexture;
	GLuint m_bottomTexture;
};