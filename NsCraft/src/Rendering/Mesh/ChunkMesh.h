#pragma once
#include <vector>
#include <GL/glew.h>
#include "Quad.h"
#include "../../OpenGL/VertexArray.h"

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

	bool isEmpty() const;
	std::shared_ptr<VertexArray> generateChunkVAO() const;
private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_textureCoords;
	std::vector<GLuint> m_indices;

	GLuint m_currentIndex;
};