#pragma once
#include <cstdint>
#include <bitset>

typedef std::uint8_t Biome_ID;

enum BiomeFlagsEnum {
	LAND = 1 << 0,
	OCEAN = 1 << 1
};

typedef std::bitset<8> BiomeFlags;