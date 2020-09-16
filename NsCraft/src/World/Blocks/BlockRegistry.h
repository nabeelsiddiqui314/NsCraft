#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "BlockDefs.h"

class Block;

class BlockRegistry {
public:
	BlockRegistry() = default;
	~BlockRegistry() = default;
public:
	Block& registerBlock(const std::string& name);
	
	Block_ID getBlockIDFromName(const std::string& name) const;

	const Block& getBlockFromID(Block_ID id) const;
	const Block& getBlockFromName(const std::string& name) const;
private:
	std::unordered_map<std::string, Block_ID> m_nameToIDMap;
	std::vector<Block> m_blocks;
};