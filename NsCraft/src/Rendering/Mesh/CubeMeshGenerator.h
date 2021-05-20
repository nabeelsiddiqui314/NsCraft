#pragma once
#include <GL/glew.h>
#include <tuple>
#include <array>
#include "IMeshGenerator.h"

class Vector2;

class CubeMeshGenerator : public IMeshGenerator {
public:
	CubeMeshGenerator(GLuint topTexture, GLuint sideTexture, GLuint bottomTexture);
	~CubeMeshGenerator() = default;
public:
	void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) override;
private:
	std::array<GLfloat, 4> getFaceAmbientLighting(const PaddedChunk& chunk, const Vector3& blockPosition, const Vector3& faceDirection) const;
	std::tuple<Vector3, Vector3, Vector3> computeVertexNeighbors(const Vector3& faceDirection, const Vector2& vertex) const;
	float getAmbientOcclusion(bool side1, bool side2, bool corner) const;
private:
	GLuint m_topTexture;
	GLuint m_sideTexture;
	GLuint m_bottomTexture;
};