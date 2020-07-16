#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "BlockDefs.h"

class IBlock;

class BlockRegistry {
private:
	typedef std::shared_ptr<IBlock> BlockPtr;
public:
	BlockRegistry() = default;
	~BlockRegistry() = default;
public:
	void registerBlock(const std::string& name, const BlockPtr& block);

	const BlockPtr& getBlockFromID(Block_ID id) const;
	const BlockPtr& getBlockFromName(const std::string& name) const;
private:
	std::unordered_map<std::string, Block_ID> m_nameToIDMap;
	std::vector<BlockPtr> m_blocks;
};