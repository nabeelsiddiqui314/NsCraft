#include "ChunkRenderer.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/Shader.h"
#include "../OpenGL/Material.h"
#include "../OpenGL/Texture.h"
#include "../Math/Frustum.h"
#include "Mesh/ChunkMesh.h"
#include "../Math/AABB.h"
#include "../World/Chunk/Chunk.h"
#include "../Rendering/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

ChunkRenderer::ChunkRenderer(const std::shared_ptr<Texture>& texture) {
	auto shader = std::make_shared<Shader>("shaders/chunkShader.vs", "shaders/chunkShader.fs");
	m_chunkMaterial = std::make_shared<Material>(shader);
	m_chunkMaterial->setCullMode(CullMode::BACK);
	m_chunkMaterial->setTexture("u_blocksTexture", texture);
}

void ChunkRenderer::addMesh(const Vector3& position, const ChunkMeshPtr& mesh) {
	m_meshToLoad.emplace(std::make_pair(position, mesh));
}


void ChunkRenderer::removeMesh(const Vector3& position) {
	m_renderableChunkMap.erase(position);
}

void ChunkRenderer::renderChunks(const Frustum& viewFrustum) {
	loadMeshes();

	for (const auto& [position, chunkVao] : m_renderableChunkMap) {
		AABB chunkBoundingBox = {position * Chunk::WIDTH, glm::vec3(Chunk::WIDTH)};

		if (viewFrustum.isAABBinFrustum(chunkBoundingBox)) {
			glm::mat4 chunkModelMatrix = glm::mat4(1.0f);
			chunkModelMatrix = glm::translate(chunkModelMatrix, glm::vec3(position * Chunk::WIDTH));

			Renderer::render(chunkVao, m_chunkMaterial, chunkModelMatrix);
		}
	}
}

void ChunkRenderer::loadMeshes() {
	while (!m_meshToLoad.empty()) {
		auto& [position, mesh] = m_meshToLoad.front();

		removeMesh(position);
		m_renderableChunkMap.emplace(std::make_pair(position, mesh->generateChunkVAO()));

		m_meshToLoad.pop();
	}
}