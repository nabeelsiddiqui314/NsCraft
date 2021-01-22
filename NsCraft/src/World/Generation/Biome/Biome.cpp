#include "Biome.h"
#include "../../../Math/Vector2.h"

Biome::Biome(Biome_ID id, const std::string& name) 
	: m_id(id), m_name(name) {}

void Biome::setTemperature(float temperature) {
	m_temperature = temperature;
}

Biome_ID Biome::getID() const {
	return m_id;
}

const std::string& Biome::getName() const {
	return m_name;
}

float Biome::getTemperature() const {
	return m_temperature;
}

void Biome::setRainfall(float rainfall) {
	m_rainfall = rainfall;
}

float Biome::getRainfall() const {
	return m_rainfall;
}

void Biome::setFlags(const BiomeFlags& flags) {
	m_flags = flags;
}

BiomeFlags Biome::getFlags() const {
	return m_flags;
}

void Biome::setNoiseProperties(const NoiseProperties& noiseProperties) {
	m_noiseProperties = noiseProperties;
}

void Biome::setComposition(const ColumnComposition& composition) {
	m_composition = composition;
}

const NoiseProperties& Biome::getNoiseProperties() const {
	return m_noiseProperties;
}

Block_ID Biome::getBlockAtDepth(int depth) const {
	if (m_composition.layers.size() == 0)
		return 0;

	int totalBlockDepth = 0;

	for (auto& layer : m_composition.layers) {
		totalBlockDepth += layer.height;

		if (depth < totalBlockDepth) {
			return layer.block;
		}
	}

	auto& layer = m_composition.layers.back();

	return layer.block;
}
