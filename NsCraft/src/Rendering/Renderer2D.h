#pragma once
#include <glm/glm.hpp>
#include <memory>

class Texture2D;

namespace Renderer2D {
	void init();

	void drawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
	void drawRect(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture);
}