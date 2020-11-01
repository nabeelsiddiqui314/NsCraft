#include "ChunkShape.h"
#include "../../../Math/Vector3.h"

void ChunkShape::setDensity(const Vector3& position, const Density& density) {
    m_densityMap[getIndex(position)] = density;
}

Density ChunkShape::getDensity(const Vector3& position) const {
    return m_densityMap[getIndex(position)];
}

void ChunkShape::setPositionData(const Vector3& position, const PositionData& data) {
    m_positionDataMap[getIndex(position)] = data;
}

PositionData ChunkShape::getPostionData(const Vector3& position) const {
    return m_positionDataMap[getIndex(position)];
}

std::size_t ChunkShape::getIndex(const Vector3& position) const {
    return position.x + Chunk::WIDTH * (position.y + Chunk::WIDTH * position.z);
}
