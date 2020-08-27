#include "ChunkRenderer.h"
#include <GL/glew.h>
#include "Mesh/ChunkMesh.h"
#include "../OpenGL/VertexArray.h"
#include "Camera/Camera.h"

ChunkRenderer::ChunkRenderer() : m_shader("shaders/basicShader.vs", "shaders/basicShader.fs") {
	m_texture.loadFromPath("res/smiley.png");
	m_texture.bind();
	m_shader.useProgram();

	glEnable(GL_DEPTH_TEST);
}

void ChunkRenderer::addMesh(const Vector3& position, const ChunkMesh& mesh) {
	m_renderableChunkMap.emplace(std::make_pair(position, mesh.generateChunkVAO()));
}

void ChunkRenderer::removeMesh(const Vector3& position) {
	m_renderableChunkMap.erase(position);
}

void ChunkRenderer::renderChunks(const Camera& camera) {
	for (const auto& [position, chunkVao] : m_renderableChunkMap) {
		chunkVao->bind();
		m_shader.setUniformMat4("u_view", camera.getView());
		m_shader.setUniformMat4("u_projection", camera.getProjection());
		glDrawElements(GL_TRIANGLES, chunkVao->getIndexCount(), GL_UNSIGNED_INT, 0);
		chunkVao->unbind();
	}
}