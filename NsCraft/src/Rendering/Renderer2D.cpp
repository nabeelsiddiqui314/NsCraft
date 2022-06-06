#include "Renderer2D.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/VertexBuffer.h"
#include "../OpenGL/IndexBuffer.h"
#include "../OpenGL/Material.h"
#include "../OpenGL/Shader.h"
#include "Renderer.h"

namespace Renderer2D {

	static std::shared_ptr<VertexArray> s_quadVao;
	static std::shared_ptr<Material> s_colorMaterial;

	void init() {
		std::vector<GLfloat> vertices = { -0.5f,  0.5f,
		                                  -0.5f, -0.5f,
		                                   0.5f, -0.5f,
		                                   0.5f,  0.5f };
		std::vector<GLuint> indices = {0, 1, 2, 2, 3, 0};

		s_quadVao = std::make_shared<VertexArray>();
		s_quadVao->bind();

		auto verticesBuffer = std::make_shared<VertexBuffer>(&vertices.front(), vertices.size());
		auto indexBuffer = std::make_shared<IndexBuffer>(&indices.front(), indices.size());

		s_quadVao->addVertexBuffer(verticesBuffer, 2);
		s_quadVao->setIndexBuffer(indexBuffer);

		auto colorShader = std::make_shared<Shader>("shaders/basicShader.vs", "shaders/colorShader.fs");
		s_colorMaterial = std::make_shared<Material>(colorShader);
	}

	glm::mat4 createModelMatrix(const glm::vec2& position, const glm::vec2& size) {
		return glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	}

	void drawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color) {
		s_colorMaterial->setVector("u_color", color);
		glm::mat4 modelMatrix = createModelMatrix(position, size);

		Renderer::submit(s_quadVao, s_colorMaterial, modelMatrix);
	}
}