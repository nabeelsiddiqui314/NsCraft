#pragma once
#include <cstdint>
#include <memory>
#include <glm/glm.hpp>

class Camera;
class VertexArray;
class Material;

class Renderer {
private:
	struct CameraMatrices {
		glm::mat4 view;
		glm::mat4 projection;
	};
public:
	static void init();

	static void resizeViewport(std::uint32_t windowWidth, std::uint32_t windowHeight);
	static void begin(const Camera& camera);
	static void render(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Material>& material, const glm::mat4& modelMatrix = glm::mat4(1.0f));
private:
	static CameraMatrices s_cameraMatrices;
};