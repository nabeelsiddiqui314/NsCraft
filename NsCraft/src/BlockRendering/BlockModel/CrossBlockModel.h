#pragma once
#include "IBlockModel.h"
#include <GL/glew.h>

class CrossBlockModel : public IBlockModel {
public:
	CrossBlockModel(GLuint texture);
	~CrossBlockModel() = default;
public:
	void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) override;
private:
	GLuint m_texture;
};