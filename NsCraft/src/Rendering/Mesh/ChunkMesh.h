#pragma once
#include <vector>
#include <GL/glew.h>
#include "Quad.h"
#include "../../OpenGL/VertexArray.h"

struct Vector3;
class TextureAtlas;

class ChunkMesh {
public:
	ChunkMesh(const TextureAtlas& textureAtlas);
	~ChunkMesh() = default;

	ChunkMesh(const ChunkMesh&) = delete;
	ChunkMesh& operator=(const ChunkMesh&) = delete;
public:
	void addQuad(const Vector3& position, const std::string& texture, const Quad& quad);

	bool isEmpty() const;
	std::shared_ptr<VertexArray> generateChunkVAO() const;
private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_textureCoords;
	std::vector<GLfloat> m_lighting;
	std::vector<GLuint> m_indices;

	const TextureAtlas& m_textureAtlas;
	GLuint m_currentIndex;
};