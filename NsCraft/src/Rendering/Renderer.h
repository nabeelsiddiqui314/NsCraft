#pragma once
#include <cstdint>
#include <memory>
#include <glm/glm.hpp>
#include <vector>

class ICamera;
class VertexArray;
class Material;

class Renderer {
private:
	struct CameraMatrices {
		glm::mat4 view;
		glm::mat4 projection;
	};

	struct RenderRequest {
		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<Material> material;
		glm::mat4 modelMatrix;
	};
public:
	static void init();

	static void resizeViewport(std::uint32_t windowWidth, std::uint32_t windowHeight);
	static void begin(const ICamera& camera);
	static void submit(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Material>& material, const glm::mat4& modelMatrix = glm::mat4(1.0f));
	static void render();
private:
	static CameraMatrices s_cameraMatrices;
	static std::vector<RenderRequest> s_renderRequests;
};