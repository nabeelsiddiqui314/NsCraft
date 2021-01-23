#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureCube.h"

Material::Material(const std::shared_ptr<Shader>& shader) 
	: m_shader(shader) {}

void Material::setScalar(const std::string& name, float value) {
	m_scalarUniforms[name] = value;
}

void Material::setVector(const std::string& name, const glm::vec3& vector) {
	m_vec3Uniforms[name] = vector;
}

void Material::setVector(const std::string& name, const glm::vec4& vector) {
	m_vec4Uniforms[name] = vector;
}

void Material::setTexture(const std::string& name, const std::shared_ptr<Texture>& texture) {
	m_textures[name] = texture;
}

void Material::setTexture(const std::string& name, const std::shared_ptr<TextureCube>& texture) {
	m_textureCubes[name] = texture;
}

void Material::bind() {
	m_shader->bind();

	for (auto& [name, scalar] : m_scalarUniforms) {
		m_shader->setUniform1f(name, scalar);
	}

	for (auto& [name, vector] : m_vec3Uniforms) {
		m_shader->setUniform3f(name, vector);
	}

	for (auto& [name, vector] : m_vec4Uniforms) {
		m_shader->setUniform4f(name, vector);
	}

	std::uint8_t textureUnit = 0;

	for (auto& [name, texture] : m_textures) {
		texture->bind(textureUnit);
		m_shader->setUniform1i(name, textureUnit);
		textureUnit++;
	}

	for (auto& [name, texture] : m_textureCubes) {
		texture->bind(textureUnit);
		m_shader->setUniform1i(name, textureUnit);
		textureUnit++;
	}
}

void Material::setCullMode(CullMode cullMode) {
	m_cullMode = cullMode;
}

CullMode Material::getCullMode() const{
	return m_cullMode;
}