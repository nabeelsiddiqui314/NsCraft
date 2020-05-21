#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GLuint* indices, GLuint size) : m_indexCount(size) {
	glGenBuffers(1, &m_iboHandle);
	
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_iboHandle);
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboHandle);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::getIndexCount() const {
	return m_indexCount;
}
