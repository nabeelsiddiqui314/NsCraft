#include "FlatHeightmapGenerator.h"
#include "Heightmap.h"
#include "../../../Math/Vector2.h"

FlatHeightmapGenerator::FlatHeightmapGenerator(int height) {
    m_flatHeightmap = std::make_shared<Heightmap>();

    for (int x = 0; x < Chunk::WIDTH; x++) {
        for (int z = 0; z < Chunk::WIDTH; z++) {
            m_flatHeightmap->setHeightAt({x, z}, height);
        }
    }
}

HeightmapPtr FlatHeightmapGenerator::generateHeightmap(const Vector2& position) {
    return m_flatHeightmap;
}
