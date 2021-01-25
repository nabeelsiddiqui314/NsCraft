#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include "../../Geometry/BlockFaces.h"
#include "../../OpenGL/VertexArray.h"
#include "../../Math/Vector3.h"

class TextureAtlas;

class ChunkMesh {
public:
	ChunkMesh(const TextureAtlas& textureAtlas);
	~ChunkMesh() = default;

	ChunkMesh(const ChunkMesh&) = delete;
	ChunkMesh& operator=(const ChunkMesh&) = delete;
public:
	void setCurrentOrigin(const Vector3& origin);
	void addQuad(const std::string& texture, const BlockFace& face, std::uint8_t skyLight, std::uint8_t naturalLight);

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
	Vector3 m_origin;
	GLuint m_currentIndex;
};