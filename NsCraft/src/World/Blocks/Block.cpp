#include "Block.h"

Block::Block(const MeshGeneratorPtr& meshGenerator) 
	: m_meshGenerator(meshGenerator) {}

Block::MeshGeneratorPtr Block::getMeshGenerator() const {
	return m_meshGenerator;
}
