#include "Texture2D.h"
#include <SFML/Graphics/Image.hpp>

Texture2D::Texture2D()
	: m_texture(0)
{}

void Texture2D::loadFromPath(const std::string& path) {
	sf::Image image;
	image.loadFromFile(path);
	loadFromImage(image);
}

void Texture2D::loadFromImage(const sf::Image& image) {
	deleteTexture();

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unbind();
}

void Texture2D::bind(GLuint slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture2D::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::deleteTexture() {
	glDeleteTextures(1, &m_texture);
}

Texture2D::~Texture2D() {
	deleteTexture();
}