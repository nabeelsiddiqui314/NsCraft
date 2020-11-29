#pragma once
#include <memory>
#include "BiomeMap.h"

struct Vector2;
//class BiomeMap;

typedef std::shared_ptr<BiomeMap> BiomeMapPtr;

class IBiomeGenerator {
public:
	IBiomeGenerator() = default;
	virtual ~IBiomeGenerator() = default;
public:
	virtual BiomeMapPtr generateBiome(const Vector2& position) {
		// temporary: until a deived class is made.
		return std::make_shared<BiomeMap>();
	}
};