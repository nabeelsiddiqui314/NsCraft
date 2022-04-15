#include "Block.h"
#include "../../Lighting/LightDefs.h"

Block::Block()
	: m_opacity(0),
      m_luminocity(0) {
}

void Block::setBlockModel(const BlockModelPtr& blockModel) {
	m_blockModel = blockModel;
}

Block::BlockModelPtr Block::getBlockModel() const {
	return m_blockModel;
}

void Block::setMaterial(const MaterialPtr& material) {
	m_material = material;
}

Block::MaterialPtr Block::getMaterial() const {
	return m_material;
}

void Block::setOpacity(std::uint8_t opacity) {
	m_opacity = std::min(opacity, LightDefs::MAX_OPACITY);
}

std::uint8_t Block::getOpacity() const {
	return m_opacity;
}

bool Block::isInvisible() const {
	return !m_blockModel;
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
