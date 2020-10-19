#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_vaoHandle);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_vaoHandle);
}

void VertexArray::bind() {
	glBindVertexArray(m_vaoHandle);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, std::size_t size) {
	bind();
	vertexBuffer->bind();

	m_vertexBuffers.push_back(vertexBuffer);

	GLuint index = m_vertexBuffers.size() - 1;

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
	bind();
	indexBuffer->bind();

	m_indexBuffer = indexBuffer;
}

GLsizei VertexArray::getIndexCount() const {
	return m_indexBuffer->getIndexCount();
}
