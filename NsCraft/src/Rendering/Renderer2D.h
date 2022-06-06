#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace Renderer2D {
	void init();

	void drawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
}