#pragma once
#include <string>
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
	void addQuad(const Vector3& position, const std::string& texture, const Quad& quad, std::uint8_t skyLight, std::uint8_t naturalLight);

	bool isEmpty() const;
	std::shared_ptr<VertexArray> generateChunkVAO() const;
private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_textureCoords;
	std::vector<GLfloat> m_faceLighting;
	std::vector<GLfloat> m_skyLight;
	std::vector<GLfloat> m_naturalLight;
	std::vector<GLuint> m_indices;

	const TextureAtlas& m_textureAtlas;
	GLuint m_currentIndex;
};