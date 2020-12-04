#include "Heightmap.h"
#include "../../../Math/Vector2.h"

void Heightmap::setHeightAt(const Vector2& position, int height) {
    m_heightMap[getIndex(position)] = height;
}

int Heightmap::getHeightAt(const Vector2& position) const {
    return m_heightMap[getIndex(position)];
}

inline std::size_t Heightmap::getIndex(const Vector2& position) const {
    return position.x + position.y * Chunk::WIDTH;
}
