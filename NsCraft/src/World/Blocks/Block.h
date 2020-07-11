#pragma once
#include <string>

typedef std::uint8_t Block_ID;

class Block {
public:
	Block(Block_ID id, const std::string& name);
	~Block() = default;
public:
	Block_ID getID() const;
	const std::string& getName() const;
private:
	Block_ID m_id;
	std::string m_name;
};