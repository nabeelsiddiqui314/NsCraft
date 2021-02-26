#include "Renderer.h"
#include <GL/glew.h>
#include "Camera/Camera.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/Shader.h"
#include "../OpenGL/Material.h"

Renderer::CameraMatrices Renderer::s_cameraMatrices;

void Renderer::init() {
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.1f);
}

void Renderer::resizeViewport(std::uint32_t windowWidth, std::uint32_t windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
}

void Renderer::begin(const Camera& camera) {
	s_cameraMatrices.view = camera.getView();
	s_cameraMatrices.projection = camera.getProjection();
}

void Renderer::render(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Material>& material, const glm::mat4& modelMatrix) {
	switch (material->getCullMode()) {
	case CullMode::BACK:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	case CullMode::FRONT:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	case CullMode::OFF:
		glDisable(GL_CULL_FACE);
		break;
	}

	switch (material->getBlendMode()) {
	case BlendMode::OPAQUE:
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
		break;
	case BlendMode::CUT_OUT:
		glEnable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
		break;
	case BlendMode::TRANSPARENT:
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		break;
	}

	auto& shader = material->m_shader;

	shader->bind();
	shader->setUniformMat4("u_model", modelMatrix);
	shader->setUniformMat4("u_view", s_cameraMatrices.view);
	shader->setUniformMat4("u_projection", s_cameraMatrices.projection);

	material->bind();

	vao->bind();
	glDrawElements(GL_TRIANGLES, vao->getIndexCount(), GL_UNSIGNED_INT, 0);
}