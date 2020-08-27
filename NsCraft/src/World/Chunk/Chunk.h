#pragma once
#include <array>
#include "../Blocks/BlockDefs.h"

struct Vector3;

class Chunk {
public:
	static constexpr int WIDTH = 16;
public:
	Chunk();
	Chunk(Block_ID blockID);
	~Chunk() = default;
public:
	void setBlock(const Vector3& position, Block_ID id);
	Block_ID getBlock(const Vector3& position) const;
private:
	std::size_t getIndex(const Vector3& position) const;
private:
	std::array<Block_ID, WIDTH * WIDTH * WIDTH> m_blocks;
};