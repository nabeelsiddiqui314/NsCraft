#include "BlockRegistry.h"
#include "Block.h"

Block& BlockRegistry::registerBlock(const std::string& name) {
	Block_ID id = static_cast<Block_ID>(m_blocks.size());
	m_blocks.emplace_back();
	m_nameToIDMap.emplace(std::make_pair(name, id));

	return m_blocks.back();
}

Block_ID BlockRegistry::getBlockIDFromName(const std::string& name) const {
	return m_nameToIDMap.at(name);
}

const Block& BlockRegistry::getBlockFromID(Block_ID id) const {
	return m_blocks[id];
}

const Block& BlockRegistry::getBlockFromName(const std::string& name) const {
	return m_blocks[static_cast<std::size_t>(getBlockIDFromName(name))];
}