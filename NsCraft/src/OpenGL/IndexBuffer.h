#pragma once
#include <GL/glew.h>

class IndexBuffer {
public:
	IndexBuffer(const GLuint* indices, GLuint size);
	~IndexBuffer();
public:
	void bind();
	void unbind();

	GLuint getIndexCount() const;
private:
	GLuint m_iboHandle;
	GLuint m_indexCount;
};