#include "ChunkMesh.h"
#include "../../Math/Vector3.h"
#include "../../Math/FloatRect.h"
#include "../../OpenGL/VertexBuffer.h"
#include "../../OpenGL/IndexBuffer.h"
#include "../TextureAtlas.h"

ChunkMesh::ChunkMesh(const TextureAtlas& textureAtlas)
	: m_textureAtlas(textureAtlas),
	  m_currentIndex(0) {}

void ChunkMesh::addQuad(const Vector3& position, const std::string& texture, const Quad& quad) {
	int faceIndex = 0;
	for (int i = 0; i < 4; i++) {
		m_vertices.emplace_back(position.x + quad[faceIndex++]);
		m_vertices.emplace_back(position.y + quad[faceIndex++]);
		m_vertices.emplace_back(position.z + quad[faceIndex++]);
	}

	FloatRect textureCoords = m_textureAtlas.getTextureCoordinates(texture);

	m_textureCoords.insert(m_textureCoords.end(), {
			textureCoords.x + textureCoords.w, textureCoords.y + textureCoords.h,
			textureCoords.x                  , textureCoords.y + textureCoords.h,
			textureCoords.x                  , textureCoords.y,
			textureCoords.x + textureCoords.w, textureCoords.y
		});

	m_indices.insert(m_indices.end(), {
			m_currentIndex,
			m_currentIndex + 1,
			m_currentIndex + 2,
			m_currentIndex,
			m_currentIndex + 2,
			m_currentIndex + 3
		});
	m_currentIndex += 4;
}

bool ChunkMesh::isEmpty() const {
	return m_vertices.empty() || m_textureCoords.empty() || m_indices.empty();
}

std::shared_ptr<VertexArray> ChunkMesh::generateChunkVAO() const {
	auto vao = std::make_shared<VertexArray>();
	vao->bind();

	auto verticesBuffer = std::make_shared<VertexBuffer>(&m_vertices.front(), m_vertices.size());
	auto textureCoordBuffer = std::make_shared<VertexBuffer>(&m_textureCoords.front(), m_textureCoords.size());
	auto indexBuffer = std::make_shared<IndexBuffer>(&m_indices.front(), m_indices.size());

	vao->addVertexBuffer(verticesBuffer, 3);
	vao->addVertexBuffer(textureCoordBuffer, 2);
	vao->setIndexBuffer(indexBuffer);

	return vao;
}
