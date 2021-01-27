#pragma once
#include <GL/glew.h>
#include <string>
#include "Texture.h"

namespace sf {
	class Image;
}

class Texture2D : public Texture {
public:
	Texture2D();
	~Texture2D();
public:
	void loadFromPath(const std::string& path);
	void loadFromImage(const sf::Image& image);
	void bind(GLuint slot = 0) override;
	void unbind() override;
private:
	void deleteTexture();
private:
	GLuint m_texture;
};