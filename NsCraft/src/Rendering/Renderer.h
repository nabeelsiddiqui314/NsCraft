#pragma once
#include <cstdint>
#include <memory>
#include <glm/glm.hpp>

class ICamera;
class VertexArray;
class Material;

namespace Renderer {

	void init();

	void resizeViewport(std::uint32_t windowWidth, std::uint32_t windowHeight);
	void begin(const ICamera& camera);
	void submit(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Material>& material, const glm::mat4& modelMatrix = glm::mat4(1.0f));
	void end();
}