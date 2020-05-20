#pragma once
#include <GL/glew.h>
#include <string>

namespace sf {
	class Image;
}

class Texture
{
public:
	Texture();
	~Texture();
public:
	void loadFromPath(const std::string& path);
	void loadFromImage(const sf::Image& image);
	void bind(std::uint8_t slot = 0);
	void unbind();
private:
	GLuint m_texture;
};