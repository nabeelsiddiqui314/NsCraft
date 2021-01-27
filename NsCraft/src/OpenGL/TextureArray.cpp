#include "TextureArray.h"
#include <SFML/Graphics/Image.hpp>

TextureArray::TextureArray(std::uint32_t width, std::uint32_t height) 
	: m_width(width), m_height(height) {
	glGenTextures(1, &m_textureArrayHandle);
}

TextureArray::~TextureArray() {
	glDeleteTextures(1, &m_textureArrayHandle);
}

GLuint TextureArray::addTexture(const std::string& filepath) {
	GLuint textureIndex = m_textureFilepaths.size();
	m_textureFilepaths.emplace_back(filepath);

	return textureIndex;
}

void TextureArray::generateArray() {
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureArrayHandle);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, m_width, m_height, m_textureFilepaths.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	for (GLint i = 0; i < m_textureFilepaths.size(); i++) {
		sf::Image imageBuffer;
		imageBuffer.loadFromFile(m_textureFilepaths[i]);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, m_width, m_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer.getPixelsPtr());
	}

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void TextureArray::bind(GLuint slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureArrayHandle);
}

void TextureArray::unbind() {
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}
