#pragma once
#include <bitset>

enum BiomeFlagsEnum {
	SPECIAL = 1 << 0
};

typedef std::bitset<8> BiomeFlags;