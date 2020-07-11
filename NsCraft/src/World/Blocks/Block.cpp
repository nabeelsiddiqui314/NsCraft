#include "Block.h"

Block::Block(Block_ID id, const std::string& name) 
	: m_id(id),
      m_name(name) {}

Block_ID Block::getID() const {
	return m_id;
}

const std::string& Block::getName() const {
	return m_name;
}
