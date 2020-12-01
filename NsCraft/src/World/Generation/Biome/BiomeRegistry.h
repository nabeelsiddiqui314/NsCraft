#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "BiomeDefs.h"

class Biome;

class BiomeRegistry {
public:
	BiomeRegistry(const BiomeRegistry&) = delete;
	BiomeRegistry(const BiomeRegistry&&) = delete;
	BiomeRegistry& operator=(const BiomeRegistry&) = delete;
	~BiomeRegistry() = default;
	static BiomeRegistry& getInstance();
private:
	BiomeRegistry() = default;
public:
	Biome& registerBiome(const std::string& name);

	const Biome& getBiomeFromName(const std::string& name) const;
	const Biome& getBiomeFromID(Biome_ID id) const;
private:
	std::vector<Biome> m_biomes;
	std::unordered_map<std::string, Biome_ID> m_nameToIdMap;
};