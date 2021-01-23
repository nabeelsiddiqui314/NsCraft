#pragma once
#include <string>
#include <queue>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics/Image.hpp>
#include "TextureCoords.h"

class Texture;

// Only supports square textures of equal width for now

class TextureAtlas {
public:
	TextureAtlas(std::uint32_t textureWidth);
	~TextureAtlas() = default;
public:
	bool addTexture(const std::string& textureFilepath, const std::string& textureName);
	std::shared_ptr<Texture> generateAtlas();

	TextureCoords getTextureCoordinates(const std::string& textureName) const;
private:
	std::uint32_t getNearestSquare(std::uint32_t value) const;
	std::uint32_t getNearestPowerOf2(std::uint32_t value) const;
private:
	const std::uint32_t m_textureWidth;
	std::shared_ptr<Texture> m_texture;

	sf::Image m_textureAtlasBuffer;
	std::queue<std::pair<std::string, sf::Image>> m_textureQueue;
	std::unordered_map<std::string, TextureCoords> m_textureCoordinateMap;
};