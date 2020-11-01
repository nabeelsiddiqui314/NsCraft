#pragma once
#include <cstdint>
#include <array>

#include "../../Chunk/Chunk.h"

struct Vector3;

enum class Density : std::uint8_t {
	VOID,
	SOLID
};

enum class PositionType {
	SURFACE,
	INTERIOR,
	BASE
};

struct PositionData {
	PositionType positionType;
	int distanceFromTop = 0;
};

class ChunkShape {
public:
	ChunkShape() = default;
	~ChunkShape() = default;
public:
	void setDensity(const Vector3& position, const Density& density);
	Density getDensity(const Vector3& position) const;

	void setPositionData(const Vector3& position, const PositionData& data);
	PositionData getPostionData(const Vector3& position) const;
private:
	std::size_t getIndex(const Vector3& position) const;
private:
	std::array<Density, Chunk::WIDTH* Chunk::WIDTH* Chunk::WIDTH> m_densityMap;
	std::array<PositionData, Chunk::WIDTH* Chunk::WIDTH* Chunk::WIDTH> m_positionDataMap;
};