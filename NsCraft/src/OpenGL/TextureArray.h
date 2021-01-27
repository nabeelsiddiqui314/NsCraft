#pragma once
#include <cstdint>
#include <string>
#include <GL/glew.h>
#include <vector>

class TextureArray {
public:
	TextureArray(std::uint32_t width, std::uint32_t height);
	~TextureArray();
public:
	GLuint addTexture(const std::string& filepath);
	void generateArray();

	void bind(std::uint8_t slot = 0);
	void unbind();
private:
	std::uint32_t m_width;
	std::uint32_t m_height;

	GLuint m_textureArrayHandle;
	std::vector<std::string> m_textureFilepaths;
};