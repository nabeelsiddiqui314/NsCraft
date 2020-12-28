#include "ChunkRenderer.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/Shader.h"
#include "../Math/Frustum.h"
#include "Mesh/ChunkMesh.h"
#include "../Math/AABB.h"
#include "../World/Chunk/Chunk.h"
#include "../Rendering/Renderer.h"

ChunkRenderer::ChunkRenderer() : m_chunkShader(std::make_shared<Shader>("shaders/chunkShader.vs", "shaders/chunkShader.fs")) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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
			Renderer::render(chunkVao, m_chunkShader);
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