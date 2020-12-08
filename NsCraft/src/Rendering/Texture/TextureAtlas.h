#pragma once
#include <string>
#include <queue>
#include <unordered_map>
#include <SFML/Graphics/Image.hpp>
#include "../../OpenGL/Texture.h"
#include "TextureCoords.h"

// Only supports square textures of equal width for now

class TextureAtlas {
public:
	TextureAtlas(std::uint32_t textureWidth);
	~TextureAtlas() = default;
public:
	bool addTexture(const std::string& textureFilepath, const std::string& textureName);
	void generateAtlas();

	TextureCoords getTextureCoordinates(const std::string& textureName) const;

	void bindTexture();
	void unbindTexture();
private:
	std::uint32_t getNearestSquare(std::uint32_t value) const;
	std::uint32_t getNearestPowerOf2(std::uint32_t value) const;
private:
	const std::uint32_t m_textureWidth;

	sf::Image m_textureAtlasBuffer;
	Texture m_texture;
	std::queue<std::pair<std::string, sf::Image>> m_textureQueue;
	std::unordered_map<std::string, TextureCoords> m_textureCoordinateMap;
};