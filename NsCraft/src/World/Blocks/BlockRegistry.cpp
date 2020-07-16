#include "BlockRegistry.h"
#include "IBlock.h"

void BlockRegistry::registerBlock(const std::string& name, const BlockPtr& block) {
	Block_ID id = static_cast<Block_ID>(m_blocks.size());
	m_blocks.emplace_back(block);
	m_nameToIDMap.emplace(std::make_pair(name, id));
}

const BlockRegistry::BlockPtr& BlockRegistry::getBlockFromID(Block_ID id) const {
	return m_blocks[id];
}

const BlockRegistry::BlockPtr& BlockRegistry::getBlockFromName(const std::string& name) const {
	return m_blocks[static_cast<std::size_t>(m_nameToIDMap.at(name))];
}