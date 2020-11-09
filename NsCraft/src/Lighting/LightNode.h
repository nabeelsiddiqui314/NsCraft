#pragma once
#include <cstdint>

class LightNode {
public:
	LightNode();
	~LightNode() = default;
public:
	void setSkyLight(std::uint8_t value);
	void setNaturalLight(std::uint8_t value);

	std::uint8_t getSkyLight() const;
	std::uint8_t getNaturalLight() const;
private:
	std::uint8_t m_lightByte;
};