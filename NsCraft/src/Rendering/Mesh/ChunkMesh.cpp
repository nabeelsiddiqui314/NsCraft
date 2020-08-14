#include "ChunkMesh.h"
#include "../../Math/Vector3.h"
#include "../../Math/FloatRect.h"
#include "../../OpenGL/VertexBuffer.h"
#include "../../OpenGL/IndexBuffer.h"

ChunkMesh::ChunkMesh() 
	: m_currentIndex(0) {}

void ChunkMesh::addQuad(const Vector3& position, const FloatRect& textureCoords, const Quad& quad) {
	int faceIndex = 0;
	for (int i = 0; i < 4; i++) {
		m_vertices.emplace_back(position.x + quad[faceIndex++]);
		m_vertices.emplace_back(position.y + quad[faceIndex++]);
		m_vertices.emplace_back(position.z + quad[faceIndex++]);
	}

	m_textureCoords.insert(m_textureCoords.end(), {
			textureCoords.x                  , textureCoords.y,
			textureCoords.x + textureCoords.w, textureCoords.y,
			textureCoords.x + textureCoords.w, textureCoords.y + textureCoords.h,
			textureCoords.x                  , textureCoords.y + textureCoords.h
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

VertexArray ChunkMesh::generateChunkVAO() const {
	VertexArray vao;

	auto verticesBuffer = std::make_shared<VertexBuffer>(&m_vertices.front(), m_vertices.size());
	auto textureCoordBuffer = std::make_shared<VertexBuffer>(&m_textureCoords.front(), m_textureCoords.size());
	auto indexBuffer = std::make_shared<IndexBuffer>(&m_indices.front(), m_indices.size());

	vao.addVertexBuffer(verticesBuffer, 3);
	vao.addVertexBuffer(textureCoordBuffer, 2);
	vao.setIndexBuffer(indexBuffer);

	return vao;
}
