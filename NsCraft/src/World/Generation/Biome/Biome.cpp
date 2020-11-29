#include "Biome.h"
#include "../../../Math/Vector2.h"

void Biome::setTemperature(float temperature) {
	m_temperature = temperature;
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
	if (depth == 0) {
		return m_composition.surfaceBlock;
	}

	int totalBlockDepth = 0;

	for (auto& [block, blockDepth] : m_composition.middleBlocks) {
		totalBlockDepth += blockDepth;

		if (depth < totalBlockDepth) {
			return block;
		}
	}

	return 0;
}
