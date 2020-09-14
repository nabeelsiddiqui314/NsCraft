#include "TextureAtlas.h"
#include <math.h>

TextureAtlas::TextureAtlas(std::uint32_t textureWidth) 
	: m_textureWidth(textureWidth) {}

bool TextureAtlas::addTexture(const std::string& textureFilepath, const std::string& textureName) {
	sf::Image texture;
	
	if (!texture.loadFromFile(textureFilepath)) {
		return false;
	}

	// This is temporary and support for rectangular textures will be added later

	auto textureSizeX = texture.getSize().x;
	auto textureSizeY = texture.getSize().y;

	if (textureSizeX == m_textureWidth && textureSizeY == m_textureWidth) {
		m_textureQueue.push(std::make_pair(textureName, texture));
		return true;
	}

	return false;
}

void TextureAtlas::generateAtlas() {
	auto gridWidth = getNearestSquare(m_textureQueue.size());
	auto textureAtlasWidth = getNearestPowerOf2(gridWidth * m_textureWidth);

	m_textureAtlasBuffer.create(textureAtlasWidth, textureAtlasWidth);

	for (std::uint32_t i = 0; !m_textureQueue.empty(); i++) {
		auto&[textureName, textureImage] = m_textureQueue.front();

		std::uint32_t texturePosX = (i % gridWidth) * m_textureWidth;
		std::uint32_t texturePosY = (i - (i % gridWidth)) / gridWidth * m_textureWidth;
		
		m_textureAtlasBuffer.copy(textureImage, texturePosX, texturePosY);

		FloatRect textureCoords;
		textureCoords.x = static_cast<float>(texturePosX)                  / static_cast<float>(textureAtlasWidth);
		textureCoords.y = static_cast<float>(texturePosY)                  / static_cast<float>(textureAtlasWidth);
		textureCoords.w = static_cast<float>(texturePosX + m_textureWidth) / static_cast<float>(textureAtlasWidth);
		textureCoords.x = static_cast<float>(texturePosY + m_textureWidth) / static_cast<float>(textureAtlasWidth);

		m_textureCoordinateMap.emplace(textureName, textureCoords);

		m_textureQueue.pop();
	}

	m_texture.loadFromImage(m_textureAtlasBuffer);
}

FloatRect TextureAtlas::getTextureCoordinates(const std::string& textureName) const {
	return m_textureCoordinateMap.at(textureName);
}

void TextureAtlas::bindTexture() {
	m_texture.bind();
}

void TextureAtlas::unbindTexture() {
	m_texture.unbind();
}

std::uint32_t TextureAtlas::getNearestSquare(std::uint32_t value) const {
	float fValue = static_cast<float>(value);
	float valueSqrt = sqrtf(fValue);

	return static_cast<std::uint32_t>(ceil(valueSqrt));
}

std::uint32_t TextureAtlas::getNearestPowerOf2(std::uint32_t value) const {
	float fValue = static_cast<float>(value);
	float log2value = log2f(fValue);

	return static_cast<std::uint32_t>(pow(2, ceil(log2value)));
}
