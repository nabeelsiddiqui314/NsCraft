#pragma once
#include "IBlockModel.h"
#include <GL/glew.h>

class LiquidBlockModel : public IBlockModel {
public:
	LiquidBlockModel(GLuint texture);
	~LiquidBlockModel() = default;
public:
	void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) override;
private:
	GLuint m_texture;
};