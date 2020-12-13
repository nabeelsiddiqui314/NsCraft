#include "Heightmap.h"

void Heightmap::setHeightAt(const Vector2& position, int height) {
    m_heightMap[position] = height;
}

int Heightmap::getHeightAt(const Vector2& position) const {
    return m_heightMap[position];
}