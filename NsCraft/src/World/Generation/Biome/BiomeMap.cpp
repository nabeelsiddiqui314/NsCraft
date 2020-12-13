#include "BiomeMap.h"

void BiomeMap::setBiomeAt(const Vector2& position, Biome_ID biome) {
    m_biomeMap[position] = biome;
}

Biome_ID BiomeMap::getBiomeAt(const Vector2& position) const {
    return m_biomeMap[position];
}