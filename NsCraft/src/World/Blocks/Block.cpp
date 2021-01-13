#include "Block.h"
#include "../../Lighting/LightDefs.h"

Block::Block()
	: m_opacity(0),
      m_luminocity(0) {
}

void Block::setMeshGenerator(const MeshGeneratorPtr& meshGenerator) {
	m_meshGenerator = meshGenerator;
}

Block::MeshGeneratorPtr Block::getMeshGenerator() const {
	return m_meshGenerator;
}

void Block::setOpacity(std::uint8_t opacity) {
	m_opacity = std::min(opacity, LightDefs::MAX_OPACITY);
}

std::uint8_t Block::getOpacity() const {
	return m_opacity;
}

bool Block::isInvisible() const {
	return !m_meshGenerator;
}

bool Block::isCompletelyOpaque() const {
	return m_opacity == LightDefs::MAX_OPACITY;
}

void Block::setLuminocity(std::uint8_t luminocity) {
	m_luminocity = std::min(luminocity, LightDefs::MAX_LUMINOCITY);
}

std::uint8_t Block::getLuminocity() const {
	return m_luminocity;
}
