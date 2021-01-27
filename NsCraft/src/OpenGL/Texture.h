#pragma once
#include <GL/glew.h>

class Texture {
public:
	Texture() = default;
	virtual ~Texture() = default;
public:
	virtual void bind(GLuint slot = 0) = 0;
	virtual void unbind() = 0;
};