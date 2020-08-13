#include "ChunkMesh.h"
#include "../../Math/Vector3.h"
#include "../../Math/FloatRect.h"

ChunkMesh::ChunkMesh() 
	: m_index(0) {}

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
			m_index,
			m_index + 1,
			m_index + 2,
			m_index,
			m_index + 2,
			m_index + 3
		});
	m_index += 4;
}