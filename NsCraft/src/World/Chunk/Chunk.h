#pragma once
#include <array>
#include "ChunkNode.h"

struct Vector3;

class Chunk {
public:
	static constexpr int WIDTH = 16;
public:
	Chunk();
	Chunk(Block_ID blockID);
	~Chunk() = default;
public:
	void setBlock(const Vector3& position, Block_ID blockID);
	Block_ID getBlock(const Vector3& position) const;

	void setSkyLight(const Vector3& position, std::uint8_t value);
	void setNaturalLight(const Vector3& position, std::uint8_t value);

	std::uint8_t getSkyLight(const Vector3& position) const;
	std::uint8_t getNaturalLight(const Vector3& position) const;

	ChunkNode getNode(const Vector3& position) const;

	bool isFullyOpaque() const;
private:
	std::size_t getIndex(const Vector3& position) const;
private:
	std::array<ChunkNode, WIDTH * WIDTH * WIDTH> m_nodes;
	std::uint32_t m_opaqueBlockCount;
};