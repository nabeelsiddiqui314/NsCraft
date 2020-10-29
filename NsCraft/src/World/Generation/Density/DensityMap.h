#pragma once
#include <cstdint>
#include <array>

#include "../../Chunk/Chunk.h"

struct Vector3;

enum class Density : std::uint8_t {
	VOID = 0,
	SOLID
};

class DensityMap {
public:
	DensityMap() = default;
	~DensityMap() = default;
public:
	void setDensity(const Vector3& position, const Density& density);
	Density getDensity(const Vector3& position) const;
private:
	std::size_t getIndex(const Vector3& position) const;
private:
	std::array<Density, Chunk::WIDTH* Chunk::WIDTH* Chunk::WIDTH> m_densityMap;
};