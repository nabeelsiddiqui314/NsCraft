#include "BiomeInterpolatedHeightGen.h"
#include "../../../Math/Vector2.h"
#include "../Biome/BiomeMap.h"
#include "../Biome/Biome.h"
#include "../Biome/BiomeRegistry.h"
#include "../Biome/IBiomeGenerator.h"
#include "Heightmap.h"
#include <unordered_map>
#include "../../../Utilities/Flat2DArray.h"

BiomeInterpolatedHeightGen::BiomeInterpolatedHeightGen(std::uint32_t seed, BiomeGenPtr biomeGenerator) 
    : m_biomeGenPtr(biomeGenerator) {
    m_heightNoise.setSeed(seed);
}

HeightmapPtr BiomeInterpolatedHeightGen::generateHeightmap(const Vector2& position, const BiomeMap& biomeMap) {
    auto heightMap = std::make_shared<Heightmap>();

    int lerpDistance = 4;

    Flat2DArray<float, Chunk::WIDTH + 1, Chunk::WIDTH + 1> sparseheightmap;

    //generates heightmap at a lower resolutuon

    for (int x = 0; x <= Chunk::WIDTH; x += lerpDistance) {
        for (int z = 0; z <= Chunk::WIDTH; z += lerpDistance) {
            sparseheightmap[{x, z}] = getHeightAt(position, { x, z });
        }
    }

    // bilinearly scales up the low res heightmap

    for (int x = 0; x < Chunk::WIDTH; x++) {
        for (int z = 0; z < Chunk::WIDTH; z++) {

            // looks redundant but integer division returns floored value
            Vector2 cellPos = (Vector2(x, z) / lerpDistance) * lerpDistance;

            float normX = (float)(x - cellPos.x) / (float)lerpDistance;
            float normZ = (float)(z - cellPos.y) / (float)lerpDistance;
           
            float topLeft = sparseheightmap    [cellPos];
            float topRight = sparseheightmap   [{cellPos.x + lerpDistance, cellPos.y               }];
            float bottomLeft = sparseheightmap [{cellPos.x               , cellPos.y + lerpDistance}];
            float bottomRight = sparseheightmap[{cellPos.x + lerpDistance, cellPos.y + lerpDistance}];
           
            float height = bilerp(normX, normZ, topLeft, topRight, bottomLeft, bottomRight);

            heightMap->setHeightAt({ x, z }, height);
        }
    }

    return heightMap;
}

float BiomeInterpolatedHeightGen::getHeightAt(const Vector2& chunkPosition, const Vector2& blockPosition) {
    float range = 9;
    float totalInfluence = 0;

    const float totalDistance = sqrt(powf(range, 2) + powf(range, 2));

    std::unordered_map<Biome_ID, float> biomeInfluenceMap;

    for (int x = -range; x <= range; x++) {
        for (int z = -range; z <= range; z ++) {
           auto offset = Vector2(x, z);
           auto [neighborChunkPos, neighborBlockPos] = getNeighborLocation(chunkPosition, blockPosition + offset);

           Biome_ID neighborBiomeID = m_biomeGenPtr->generateBiome(neighborChunkPos)->getBiomeAt(neighborBlockPos);

            float influence = totalDistance - sqrt(powf(x, 2) + powf(z, 2));
            totalInfluence += influence;

            biomeInfluenceMap[neighborBiomeID] += influence;
        }
    }

    auto& biomeRegistry = BiomeRegistry::getInstance();

    float totalHeight = 0;

    for (auto& [biomeID, influence] : biomeInfluenceMap) {
        auto& biome = biomeRegistry.getBiomeFromID(biomeID);
        m_heightNoise.setNoiseProperties(biome.getNoiseProperties());

        float height = m_heightNoise.getNoiseAt(chunkPosition * Chunk::WIDTH + blockPosition) * influence;
        totalHeight += height;
    }

    return totalHeight / totalInfluence;
}

std::pair<Vector2, Vector2> BiomeInterpolatedHeightGen::getNeighborLocation(const Vector2& chunkPosition, 
                                                                            const Vector2& blockPosition) const {

    auto newChunkPosition = chunkPosition;
    auto newBlockPosition = blockPosition;

    if (newBlockPosition.x < 0) {
        newBlockPosition.x = Chunk::WIDTH - abs(newBlockPosition.x);
        newChunkPosition.x -= 1;
    }

    if (newBlockPosition.x >= Chunk::WIDTH) {
        newBlockPosition.x = newBlockPosition.x % Chunk::WIDTH;
        newChunkPosition.x += 1;
    }

    if (newBlockPosition.y < 0) {
        newBlockPosition.y = Chunk::WIDTH - abs(newBlockPosition.y);
        newChunkPosition.y -= 1;
    }

    if (newBlockPosition.y >= Chunk::WIDTH) {
        newBlockPosition.y = newBlockPosition.y % Chunk::WIDTH;
        newChunkPosition.y += 1;
    }

    return {newChunkPosition, newBlockPosition};
}

float BiomeInterpolatedHeightGen::lerp(float x, float a, float b) const {
    return a + x * (b - a);
}

float BiomeInterpolatedHeightGen::bilerp(float x, float y, float topLeft, float topRight, float bottomLeft, float bottomRight) const {
    float lerpTop = lerp(x, topLeft, topRight);
    float lerpBottom = lerp(x, bottomLeft, bottomRight);

    return lerp(y, lerpTop, lerpBottom);
}
