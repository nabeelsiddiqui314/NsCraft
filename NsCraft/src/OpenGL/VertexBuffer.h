#pragma once
#include <GL/glew.h>

class VertexBuffer {
public:
	VertexBuffer(const GLfloat* data, GLuint size);
	~VertexBuffer();
public:
	void bind();
	void unbind();
private:
	GLuint m_vboHandle;
};