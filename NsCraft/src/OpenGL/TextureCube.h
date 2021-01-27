#pragma once
#include <string>
#include <GL/glew.h>
#include "Texture.h"

struct FaceTextures {
	std::string top;
	std::string bottom;
	std::string left;
	std::string right;
	std::string front;
	std::string back;
};

class TextureCube : public Texture {
public:
	TextureCube(const FaceTextures& textures);
	~TextureCube();
public:
	void bind(GLuint slot = 0) override;
	void unbind() override;
private:
	GLuint m_textureHandle;
};