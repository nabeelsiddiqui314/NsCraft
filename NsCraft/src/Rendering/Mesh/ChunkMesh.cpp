#include "ChunkMesh.h"
#include "../../Math/Vector3.h"
#include "../Texture/TextureCoords.h"
#include "../../OpenGL/VertexBuffer.h"
#include "../../OpenGL/IndexBuffer.h"

ChunkMesh::ChunkMesh()
	: m_currentIndex(0) {}

void ChunkMesh::setCurrentOrigin(const Vector3& origin) {
	m_origin = origin;
}

void ChunkMesh::addQuad(GLuint textureIndex, const BlockFace& face, std::uint8_t skyLight, std::uint8_t naturalLight,
                        const std::array<GLfloat, 4>& ambientLight) {
	int faceIndex = 0;
	for (int i = 0; i < 4; i++) {
		m_vertices.emplace_back(m_origin.x + face.vertices[faceIndex++]);
		m_vertices.emplace_back(m_origin.y + face.vertices[faceIndex++]);
		m_vertices.emplace_back(m_origin.z + face.vertices[faceIndex++]);

		m_ambientLight.emplace_back(ambientLight[i]);

		m_faceLighting.emplace_back(face.faceLight);

		float skyLightNormalized = (float)skyLight / 16.0f;
		float naturalLightNormalized = (float)naturalLight / 16.0f;

		m_skyLight.emplace_back(skyLightNormalized);
		m_naturalLight.emplace_back(naturalLightNormalized);
		m_textureIndices.emplace_back(textureIndex);
	}

	m_textureCoords.insert(m_textureCoords.end(), {
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		});

	for (auto& index : BlockFaces::indicesOrder) {
		m_indices.emplace_back(m_currentIndex + index);
	}

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
	auto textureIndexBuffer = std::make_shared<VertexBuffer>(&m_textureIndices.front(), m_textureIndices.size());
	auto faceLightBuffer = std::make_shared<VertexBuffer>(&m_faceLighting.front(), m_faceLighting.size());
	auto skyLightBuffer = std::make_shared<VertexBuffer>(&m_skyLight.front(), m_skyLight.size());
	auto naturalLightBuffer = std::make_shared<VertexBuffer>(&m_naturalLight.front(), m_naturalLight.size());
	auto ambientLightBuffer = std::make_shared<VertexBuffer>(&m_ambientLight.front(), m_ambientLight.size());
	auto indexBuffer = std::make_shared<IndexBuffer>(&m_indices.front(), m_indices.size());

	vao->addVertexBuffer(verticesBuffer, 3);
	vao->addVertexBuffer(textureCoordBuffer, 2);
	vao->addVertexBuffer(textureIndexBuffer, 1);
	vao->addVertexBuffer(faceLightBuffer, 1);
	vao->addVertexBuffer(skyLightBuffer, 1);
	vao->addVertexBuffer(naturalLightBuffer, 1);
	vao->addVertexBuffer(ambientLightBuffer, 1);
	vao->setIndexBuffer(indexBuffer);

	return vao;
}
