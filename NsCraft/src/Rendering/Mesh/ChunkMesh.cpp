#include "ChunkMesh.h"
#include "../../Math/Vector3.h"
#include "../Texture/TextureCoords.h"
#include "../../OpenGL/VertexBuffer.h"
#include "../../OpenGL/IndexBuffer.h"
#include "../Texture/TextureAtlas.h"

ChunkMesh::ChunkMesh(const TextureAtlas& textureAtlas)
	: m_textureAtlas(textureAtlas),
	  m_currentIndex(0) {}

void ChunkMesh::addQuad(const Vector3& position, const std::string& texture, const Quad& quad, std::uint8_t skyLight, std::uint8_t naturalLight) {
	int faceIndex = 0;
	for (int i = 0; i < 4; i++) {
		m_vertices.emplace_back(position.x + quad.vertices[faceIndex++]);
		m_vertices.emplace_back(position.y + quad.vertices[faceIndex++]);
		m_vertices.emplace_back(position.z + quad.vertices[faceIndex++]);

		m_faceLighting.emplace_back(quad.faceLight);

		float skyLightNormalized = (float)skyLight / 16.0f;
		float naturalLightNormalized = (float)naturalLight / 16.0f;

		m_skyLight.emplace_back(skyLightNormalized);
		m_naturalLight.emplace_back(naturalLightNormalized);
	}

	TextureCoords textureCoords = m_textureAtlas.getTextureCoordinates(texture);

	m_textureCoords.insert(m_textureCoords.end(), {
			textureCoords.bottomLeftU, textureCoords.topRightV,
			textureCoords.topRightU  , textureCoords.topRightV,
			textureCoords.topRightU  , textureCoords.bottomLeftV,
			textureCoords.bottomLeftU, textureCoords.bottomLeftV
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
	auto faceLightBuffer = std::make_shared<VertexBuffer>(&m_faceLighting.front(), m_faceLighting.size());
	auto skyLightBuffer = std::make_shared<VertexBuffer>(&m_skyLight.front(), m_skyLight.size());
	auto naturalLightBuffer = std::make_shared<VertexBuffer>(&m_naturalLight.front(), m_naturalLight.size());
	auto indexBuffer = std::make_shared<IndexBuffer>(&m_indices.front(), m_indices.size());

	vao->addVertexBuffer(verticesBuffer, 3);
	vao->addVertexBuffer(textureCoordBuffer, 2);
	vao->addVertexBuffer(faceLightBuffer, 1);
	vao->addVertexBuffer(skyLightBuffer, 1);
	vao->addVertexBuffer(naturalLightBuffer, 1);
	vao->setIndexBuffer(indexBuffer);

	return vao;
}
