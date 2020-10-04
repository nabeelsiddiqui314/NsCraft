#include "ChunkRenderer.h"
#include <GL/glew.h>
#include "../OpenGL/VertexArray.h"
#include "Camera/Camera.h"
#include "Mesh/ChunkMesh.h"

ChunkRenderer::ChunkRenderer() : m_chunkShader("shaders/chunkShader.vs", "shaders/chunkShader.fs") {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void ChunkRenderer::addMesh(const Vector3& position, const ChunkMeshPtr& mesh) {
	m_meshToLoad.emplace(std::make_pair(position, mesh));
}


void ChunkRenderer::removeMesh(const Vector3& position) {
	m_renderableChunkMap.erase(position);
}

void ChunkRenderer::renderChunks(const Camera& camera) {
	loadMeshes();

	m_chunkShader.bind();
	for (const auto& [position, chunkVao] : m_renderableChunkMap) {
		chunkVao->bind();
		m_chunkShader.setUniformMat4("u_view", camera.getView());
		m_chunkShader.setUniformMat4("u_projection", camera.getProjection());
		glDrawElements(GL_TRIANGLES, chunkVao->getIndexCount(), GL_UNSIGNED_INT, 0);
		chunkVao->unbind();
	}
	m_chunkShader.unbind();
}

void ChunkRenderer::loadMeshes() {
	while (!m_meshToLoad.empty()) {
		auto& [position, mesh] = m_meshToLoad.front();

		removeMesh(position);
		m_renderableChunkMap.emplace(std::make_pair(position, mesh->generateChunkVAO()));

		m_meshToLoad.pop();
	}
}