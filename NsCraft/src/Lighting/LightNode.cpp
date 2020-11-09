#include "LightNode.h"

LightNode::LightNode() 
	: m_lightByte(0) {}

void LightNode::setSkyLight(std::uint8_t value) {
	m_lightByte = (m_lightByte & 0xF) | (value << 4);
}

void LightNode::setNaturalLight(std::uint8_t value) {
	m_lightByte = (m_lightByte & 0xF0) | value;
}

std::uint8_t LightNode::getSkyLight() const {
	return (m_lightByte >> 4) & 0xF;
}

std::uint8_t LightNode::getNaturalLight() const {
	return m_lightByte & 0xF;
}