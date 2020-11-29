#include "BiomeMap.h"
#include "../../../Math/Vector2.h"

void BiomeMap::setBiomeAt(const Vector2& position, Biome_ID biome) {
    m_biomeMap[getIndex(position)] = biome;
}

Biome_ID BiomeMap::getBiomeAt(const Vector2& position) const {
    return m_biomeMap[getIndex(position)];
}

inline std::size_t BiomeMap::getIndex(const Vector2& position) const {
    return position.x + position.y * Chunk::WIDTH;
}
