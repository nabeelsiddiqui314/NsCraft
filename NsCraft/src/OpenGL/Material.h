#pragma once
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>

class Shader;
class Texture;
class TextureCube;
class Renderer;

enum class CullMode {
	BACK = 0,
	FRONT,
	OFF
};

class Material {
	friend Renderer;
public:
	Material(const std::shared_ptr<Shader>& shader);
	~Material() = default;
public:
	void setScalar(const std::string& name, float value);
	
	void setVector(const std::string& name, const glm::vec3& vector);
	void setVector(const std::string& name, const glm::vec4& vector);
	
	void setTexture(const std::string& name, const std::shared_ptr<Texture>& texture);
	void setTexture(const std::string& name, const std::shared_ptr<TextureCube>& texture);
	
	void bind();

	void setCullMode(CullMode cullMode);
	CullMode getCullMode() const;
private:
	std::shared_ptr<Shader> m_shader;
	std::unordered_map<std::string, float> m_scalarUniforms;
	std::unordered_map<std::string, glm::vec3> m_vec3Uniforms;
	std::unordered_map<std::string, glm::vec4> m_vec4Uniforms;
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
	std::unordered_map<std::string, std::shared_ptr<TextureCube>> m_textureCubes;

	CullMode m_cullMode = CullMode::BACK;
};