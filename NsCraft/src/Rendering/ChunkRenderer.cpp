#include "ChunkRenderer.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/Shader.h"
#include "../OpenGL/Material.h"
#include "../OpenGL/Texture.h"
#include "../Math/Frustum.h"
#include "../Math/AABB.h"
#include "../World/Chunk/Chunk.h"
#include "../Rendering/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

ChunkRenderer::ChunkRenderer() {}

void ChunkRenderer::enqueueMesh(const Vector3& position, const FullMeshPtr& meshes) {
	m_meshToLoad.emplace(std::make_pair(position, meshes));
}


void ChunkRenderer::removeChunk(const Vector3& position) {
	m_renderableChunkMap.erase(position);
}

void ChunkRenderer::renderChunks(const Frustum& viewFrustum) {
	loadMeshes();

	for (const auto& [position, renderables] : m_renderableChunkMap) {
		AABB chunkBoundingBox = {position * Chunk::WIDTH, glm::vec3(Chunk::WIDTH)};

		if (viewFrustum.isAABBinFrustum(chunkBoundingBox)) {
			glm::mat4 chunkModelMatrix = glm::mat4(1.0f);
			chunkModelMatrix = glm::translate(chunkModelMatrix, glm::vec3(position * Chunk::WIDTH));

			for (auto& renderable : renderables) {
				Renderer::submit(renderable.vao, renderable.material, chunkModelMatrix);
			}
		}
	}
}

void ChunkRenderer::loadMeshes() {
	while (!m_meshToLoad.empty()) {
		auto& [position, mesh] = m_meshToLoad.front();

 		if (!mesh->isCompletelyEmpty()) {
			m_renderableChunkMap.erase(position);
			m_renderableChunkMap.emplace(std::make_pair(position, mesh->getRenderables()));
		}

		m_meshToLoad.pop();
	}
}