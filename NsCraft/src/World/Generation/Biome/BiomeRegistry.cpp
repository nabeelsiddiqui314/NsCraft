#include "BiomeRegistry.h"
#include "Biome.h"

BiomeRegistry& BiomeRegistry::getInstance() {
    static BiomeRegistry instance;
    return instance;
}

Biome& BiomeRegistry::registerBiome(const std::string& name) {
    Biome_ID id = static_cast<Biome_ID>(m_biomes.size());
    m_biomes.emplace_back();
    m_nameToIdMap.emplace(std::make_pair(name, id));

    return m_biomes.back();
}

const Biome& BiomeRegistry::getBiomeFromName(const std::string& name) const {
    return m_biomes[m_nameToIdMap.at(name)];
}

const Biome& BiomeRegistry::getBiomeFromID(Biome_ID id) const {
    return m_biomes[id];
}