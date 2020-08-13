#pragma once
#include <vector>
#include <GL/glew.h>
#include "Quad.h"

struct Vector3;
struct FloatRect;

class ChunkMesh {
public:
	ChunkMesh();
	~ChunkMesh() = default;

	ChunkMesh(const ChunkMesh&) = delete;
	ChunkMesh& operator=(const ChunkMesh&) = delete;
public:
	void addQuad(const Vector3& position, const FloatRect& textureCoords, const Quad& quad);
private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_textureCoords;
	std::vector<GLint> m_indices;

	int m_index;
};