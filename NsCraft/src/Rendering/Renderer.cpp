#include "Renderer.h"
#include <GL/glew.h>
#include "Camera/Camera.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/Shader.h"

Renderer::CameraMatrices Renderer::s_cameraMatrices;

void Renderer::resizeViewport(std::uint32_t windowWidth, std::uint32_t windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
}

void Renderer::begin(const Camera& camera) {
	s_cameraMatrices.view = camera.getView();
	s_cameraMatrices.projection = camera.getProjection();
}

void Renderer::render(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Shader>& shader, const glm::mat4& modelMatrix) {
	shader->bind();

	shader->setUniformMat4("u_model", modelMatrix);
	shader->setUniformMat4("u_view", s_cameraMatrices.view);
	shader->setUniformMat4("u_projection", s_cameraMatrices.projection);

	vao->bind();
	glDrawElements(GL_TRIANGLES, vao->getIndexCount(), GL_UNSIGNED_INT, 0);
}