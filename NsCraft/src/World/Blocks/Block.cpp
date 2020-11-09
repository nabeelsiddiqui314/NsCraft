#include "Block.h"
#include "../../Rendering/Mesh/EmptyMeshGenerator.h"

Block::Block()
	: m_meshGenerator(std::make_shared<EmptyMeshGenerator>()),
      m_isOpaque(false),
      m_luminocity(0) {}

void Block::setMeshGenerator(const MeshGeneratorPtr& meshGenerator) {
	m_meshGenerator = meshGenerator;
}

Block::MeshGeneratorPtr Block::getMeshGenerator() const {
	return m_meshGenerator;
}

void Block::setOpaqueness(bool opaqueness) {
	m_isOpaque = opaqueness;
}

bool Block::isOpaque() const {
	return m_isOpaque;
}

void Block::setLuminocity(std::uint8_t luminocity) {
	m_luminocity = luminocity;
}

std::uint8_t Block::getLuminocity() const {
	return m_luminocity;
}
