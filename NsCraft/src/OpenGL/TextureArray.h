#pragma once
#include <cstdint>
#include <string>
#include <GL/glew.h>
#include <vector>
#include "Texture.h"

class TextureArray : public Texture {
public:
	TextureArray(std::uint32_t width, std::uint32_t height);
	~TextureArray();
public:
	GLuint addTexture(const std::string& filepath);
	void generateArray();

	void bind(GLuint slot = 0) override;
	void unbind() override;
private:
	std::uint32_t m_width;
	std::uint32_t m_height;

	GLuint m_textureArrayHandle;
	std::vector<std::string> m_textureFilepaths;
};