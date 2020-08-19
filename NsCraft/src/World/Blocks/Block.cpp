#include "Block.h"

Block::Block(const MeshGeneratorPtr& meshGenerator, bool isOpaque)
	: m_meshGenerator(meshGenerator),
      m_isOpaque(isOpaque) {}

Block::MeshGeneratorPtr Block::getMeshGenerator() const {
	return m_meshGenerator;
}

bool Block::isOpaque() const {
	return m_isOpaque;
}
