#include "BlockRegistry.h"
#include "Block.h"

void BlockRegistry::registerBlock(const std::string& name, const BlockPtr& block) {
	Block_ID id = static_cast<Block_ID>(m_blocks.size());
	m_blocks.push_back(block);
	m_nameToIDMap.emplace(std::make_pair(name, id));
}

const BlockRegistry::BlockPtr& BlockRegistry::getBlockFromID(Block_ID id) const {
	return m_blocks[id];
}

Block_ID BlockRegistry::getBlockIDFromName(const std::string& name) const {
	return m_nameToIDMap.at(name);
}

const BlockRegistry::BlockPtr& BlockRegistry::getBlockFromName(const std::string& name) const {
	return m_blocks[static_cast<std::size_t>(getBlockIDFromName(name))];
}