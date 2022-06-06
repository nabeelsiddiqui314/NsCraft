#include "Renderer2D.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/VertexBuffer.h"
#include "../OpenGL/IndexBuffer.h"
#include "../OpenGL/Material.h"
#include "../OpenGL/Shader.h"
#include "../OpenGL/Texture2D.h"
#include "Renderer.h"

namespace Renderer2D {

	static std::shared_ptr<VertexArray> s_quadVao;
	static std::shared_ptr<Material> s_colorMaterial;
	static std::shared_ptr<Material> s_textureMaterial;

	void init() {
		std::vector<GLfloat> vertices = { -0.5f,  0.5f,
		                                  -0.5f, -0.5f,
		                                   0.5f, -0.5f,
		                                   0.5f,  0.5f };

		std::vector<GLfloat> texCoords = { 0.0f, 1.0f,
		                                   0.0f, 0.0f,
		                                   1.0f, 0.0f,
		                                   1.0f, 1.0f };

		std::vector<GLuint> indices = {0, 1, 2, 2, 3, 0};

		s_quadVao = std::make_shared<VertexArray>();
		s_quadVao->bind();

		auto verticesBuffer = std::make_shared<VertexBuffer>(&vertices.front(), vertices.size());
		auto texCoordBuffer = std::make_shared<VertexBuffer>(&texCoords.front(), texCoords.size());
		auto indexBuffer = std::make_shared<IndexBuffer>(&indices.front(), indices.size());

		s_quadVao->addVertexBuffer(verticesBuffer, 2);
		s_quadVao->addVertexBuffer(texCoordBuffer, 2);
		s_quadVao->setIndexBuffer(indexBuffer);

		auto colorShader = std::make_shared<Shader>("shaders/basicShader.vs", "shaders/colorShader.fs");
		s_colorMaterial = std::make_shared<Material>(colorShader);

		auto textureShader = std::make_shared<Shader>("shaders/textureShader.vs", "shaders/textureShader.fs");
		s_textureMaterial = std::make_shared<Material>(textureShader);
		s_textureMaterial->setBlendMode(BlendMode::CUT_OUT);
	}

	glm::mat4 createModelMatrix(const glm::vec2& position, const glm::vec2& size) {
		return glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	}

	void drawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color) {
		s_colorMaterial->setVector("u_color", color);
		glm::mat4 modelMatrix = createModelMatrix(position, size);

		Renderer::submit(s_quadVao, s_colorMaterial, modelMatrix);
	}
	void drawRect(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture) {
		glm::mat4 modelMatrix = createModelMatrix(position, size);
		s_textureMaterial->setTexture("u_texture", texture);
		Renderer::submit(s_quadVao, s_textureMaterial, modelMatrix);
	}
}