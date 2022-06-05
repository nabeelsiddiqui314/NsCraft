#pragma once
#include <glm/glm.hpp>
#include <memory>

class Texture2D;
class OrthographicCamera;

namespace Renderer2D {
	void init();

	void drawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
}