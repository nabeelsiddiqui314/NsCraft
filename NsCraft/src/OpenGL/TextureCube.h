#pragma once
#include <string>
#include <GL/glew.h>

struct FaceTextures {
	std::string top;
	std::string bottom;
	std::string left;
	std::string right;
	std::string front;
	std::string back;
};

class TextureCube {
public:
	TextureCube(const FaceTextures& textures);
	~TextureCube();
public:
	void bind();
	void unbind();
private:
	GLuint m_textureHandle;
};