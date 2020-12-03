#pragma once
#include <vector>
#include "../../Blocks/BlockDefs.h"
#include "../../../Math/Noise.h"
#include "BiomeDefs.h"

struct ColumnComposition {
	Block_ID surfaceBlock;
	std::vector<std::pair<Block_ID, int>> middleBlocks;
};

class Biome {
public:
	Biome() = default;
	~Biome() = default;
public:
	void setTemperature(float temperature);
	float getTemperature() const;

	void setRainfall(float rainfall);
	float getRainfall() const;

	void setFlags(const BiomeFlags& flags);
	BiomeFlags getFlags() const;

	void setNoiseProperties(const NoiseProperties& noiseProperties);
	void setComposition(const ColumnComposition& composition);

	const NoiseProperties& getNoiseProperties() const;
	Block_ID getBlockAtDepth(int depth) const;
private:
	float m_temperature;
	float m_rainfall;
	BiomeFlags m_flags;
	NoiseProperties m_noiseProperties;
	ColumnComposition m_composition;
};