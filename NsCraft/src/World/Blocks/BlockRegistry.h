#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class Block;
typedef std::uint8_t Block_ID;

class BlockRegistry {
private:
	typedef std::unique_ptr<Block> BlockPtr;
public:
	BlockRegistry() = default;
	~BlockRegistry() = default;
public:
	const BlockPtr& registerBlock(const std::string& name);

	const BlockPtr& getBlockFromID(Block_ID id) const;
	const BlockPtr& getBlockFromName(const std::string& name) const;
private:
	std::unordered_map<std::string, Block_ID> m_nameToIDMap;
	std::vector<BlockPtr> m_blocks;
};