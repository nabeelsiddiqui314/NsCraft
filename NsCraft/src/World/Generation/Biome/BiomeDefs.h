#pragma once
#include <cstdint>
#include <bitset>

typedef std::uint8_t Biome_ID;

enum BiomeFlagsEnum {
	SPECIAL = 1 << 0
};

typedef std::bitset<8> BiomeFlags;