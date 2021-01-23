#include "TextureCube.h"
#include <vector>
#include <SFML/Graphics/Image.hpp>

TextureCube::TextureCube(const FaceTextures& textures) {
	std::vector<std::string> texturesVec;

	// textures need to be in this order to correspond to appropriate gl enums
	texturesVec.emplace_back(textures.right);
	texturesVec.emplace_back(textures.left);
	texturesVec.emplace_back(textures.top);
	texturesVec.emplace_back(textures.bottom);
	texturesVec.emplace_back(textures.front);
	texturesVec.emplace_back(textures.back);

	glGenTextures(1, &m_textureHandle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureHandle);

	for (std::uint32_t i = 0; i < texturesVec.size(); i++) {
		sf::Image imageBuffer;
		imageBuffer.loadFromFile(texturesVec[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageBuffer.getSize().x, imageBuffer.getSize().y,
			         0, GL_RGB, GL_UNSIGNED_BYTE, imageBuffer.getPixelsPtr());
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

TextureCube::~TextureCube() {
	glDeleteTextures(1, &m_textureHandle);
}

void TextureCube::bind(std::uint8_t slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureHandle);
}

void TextureCube::unbind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}