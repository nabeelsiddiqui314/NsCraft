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

    properties.octaves = 3;
    properties.smoothness = 500;
    properties.lacunarity = 2;
    properties.variation = 10;

    properties.warpOctaves = 5;
    properties.warpFrequency = 0.02f;
    properties.warpLacunarity = 2.60f;
    properties.warpAmplitude = 40;
    properties.warpGain = 0.8f;

    m_landOceanNoise.setNoiseProperties(properties);

    properties.octaves = 3;
    properties.smoothness = 500;
    properties.lacunarity = 4;
    properties.variation = 10;

    properties.warpOctaves = 5;
    properties.warpFrequency = 0.015f;
    properties.warpLacunarity = 2.40f;
    properties.warpAmplitude = 27;

    m_temperatureNoise.setNoiseProperties(properties);

    properties.octaves = 3;
    properties.smoothness = 500;
    properties.lacunarity = 4;
    properties.variation = 10;

    properties.warpOctaves = 5;
    properties.warpFrequency = 0.015f;
    properties.warpLacunarity = 2.40f;
    properties.warpAmplitude = 27;

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