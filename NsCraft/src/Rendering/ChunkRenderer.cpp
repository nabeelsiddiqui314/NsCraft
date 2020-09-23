#include "ChunkRenderer.h"
#include <GL/glew.h>
#include "Mesh/ChunkMesh.h"
#include "../OpenGL/VertexArray.h"
#include "Camera/Camera.h"

ChunkRenderer::ChunkRenderer() : m_chunkShader("shaders/chunkShader.vs", "shaders/chunkShader.fs") {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void ChunkRenderer::addMesh(const Vector3& position, const ChunkMesh& mesh) {
	removeMesh(position);
	m_renderableChunkMap.emplace(std::make_pair(position, mesh.generateChunkVAO()));
}

void ChunkRenderer::removeMesh(const Vector3& position) {
	m_renderableChunkMap.erase(position);
}

void ChunkRenderer::renderChunks(const Camera& camera) {
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