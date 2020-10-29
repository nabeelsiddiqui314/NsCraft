#include "DensityMap.h"
#include "../../../Math/Vector3.h"

void DensityMap::setDensity(const Vector3& position, const Density& density) {
    m_densityMap[getIndex(position)] = density;
}

Density DensityMap::getDensity(const Vector3& position) const {
    return m_densityMap[getIndex(position)];
}

std::size_t DensityMap::getIndex(const Vector3& position) const {
    return position.x + Chunk::WIDTH * (position.y + Chunk::WIDTH * position.z);
}
