#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const GLfloat* data, GLuint size) {
	glGenBuffers(1, &m_vboHandle);

	bind();
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_vboHandle);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}