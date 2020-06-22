#pragma once
#include <memory>
#include <vector>
#include <GL/glew.h>

class VertexBuffer;
class IndexBuffer;

class VertexArray {
public:
	VertexArray() = default;
	~VertexArray() =default;
public:
	void bind();
	void unbind();

	void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, std::size_t size);
	void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
private:
	GLuint m_vaoHandle;
	std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
	std::shared_ptr<IndexBuffer> m_indexBuffer;
};