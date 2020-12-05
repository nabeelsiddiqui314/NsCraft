#include "PerlinBiomeGenerator.h"
#include "../../../Math/Vector2.h"
#include "Biome.h"
#include "BiomeMap.h"
#include "BiomeRegistry.h"

PerlinBiomeGenerator::PerlinBiomeGenerator(std::uint32_t seed) {
    m_landOceanNoise.setSeed(seed);
    m_temperatureNoise.setSeed(seed + 4234);
    m_temperatureNoise.setSeed(seed + 9675);

    NoiseProperties properties;

    properties.amplitude = 10;
    properties.smoothness = 500;
    properties.octaves = 1;
    properties.persistance = 1;
    properties.lacunarity = 1;

    m_landOceanNoise.setNoiseProperties(properties);

    properties.amplitude = 10;
    properties.smoothness = 200;
    properties.octaves = 1;
    properties.persistance = 1;
    properties.lacunarity = 1;

    m_temperatureNoise.setNoiseProperties(properties);

    properties.amplitude = 10;
    properties.smoothness = 200;
    properties.octaves = 1;
    properties.persistance = 1;
    properties.lacunarity = 1;

    m_rainfallNoise.setNoiseProperties(properties);

}

BiomeMapPtr PerlinBiomeGenerator::generateBiome(const Vector2& position) {
    auto biomeMap = std::make_shared<BiomeMap>();

    auto& biomeRegistry = BiomeRegistry::getInstance();

    for (int x = 0; x < Chunk::WIDTH; x++) {
        for (int z = 0; z < Chunk::WIDTH; z++) {
            Vector2 worldPosition = position * Chunk::WIDTH + Vector2(x, z);

            float temperature = m_temperatureNoise.getNoiseAt(worldPosition);
            float rainfall = m_rainfallNoise.getNoiseAt(worldPosition);

            Biome_ID biome;

            if (m_landOceanNoise.getNoiseAt(worldPosition) < 5) { // land
                biome = biomeRegistry.getBiomeFromClimate(temperature, rainfall, LAND).getID();
            }
            else { //ocean
                biome = biomeRegistry.getBiomeFromClimate(temperature, rainfall, OCEAN).getID();
            }

            biomeMap->setBiomeAt({x, z}, biome);
        }
    }

    return biomeMap;
}