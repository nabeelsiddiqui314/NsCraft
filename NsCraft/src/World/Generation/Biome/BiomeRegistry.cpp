#include "BiomeRegistry.h"
#include "Biome.h"
#include <algorithm>

BiomeRegistry& BiomeRegistry::getInstance() {
    static BiomeRegistry instance;
    return instance;
}

Biome& BiomeRegistry::registerBiome(const std::string& name) {
    Biome_ID id = static_cast<Biome_ID>(m_biomes.size());
    m_biomes.emplace_back(id, name);
    m_nameToIdMap.emplace(std::make_pair(name, id));

    return m_biomes.back();
}

const Biome& BiomeRegistry::getBiomeFromName(const std::string& name) const {
    return m_biomes[m_nameToIdMap.at(name)];
}

const Biome& BiomeRegistry::getBiomeFromID(Biome_ID id) const {
    return m_biomes[id];
}

const Biome& BiomeRegistry::getBiomeFromClimate(float temperature, float rainfall, const BiomeFlags& filters) {
    std::vector<std::pair<Biome_ID, float>> filteredBiomes;

    for (int i = 0; i < m_biomes.size(); i++) {
        if (m_biomes[i].getFlags() == filters) {
            float distance = pow(temperature - m_biomes[i].getTemperature(), 2) + pow(rainfall - m_biomes[i].getRainfall(), 2);
            filteredBiomes.emplace_back(std::make_pair(i, distance));
        }
    }

    if (!filteredBiomes.empty()) {
        std::sort(filteredBiomes.begin(), filteredBiomes.end(), [](auto& left, auto& right) {
            return left.second < right.second;
        });

        auto& [biomeID, distance] = filteredBiomes[0];
        return m_biomes[biomeID];
    }

    return m_biomes[0];
}