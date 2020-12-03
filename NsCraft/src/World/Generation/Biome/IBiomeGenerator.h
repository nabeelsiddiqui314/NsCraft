#pragma once
#include <memory>

struct Vector2;
class BiomeMap;

typedef std::shared_ptr<BiomeMap> BiomeMapPtr;

class IBiomeGenerator {
public:
	IBiomeGenerator() = default;
	virtual ~IBiomeGenerator() = default;
public:
	virtual BiomeMapPtr generateBiome(const Vector2& position) = 0;
};