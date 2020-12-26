#pragma once
#include <vector>
#include "../../Blocks/BlockDefs.h"
#include "../../../Math/SimplexNoise.h"
#include "BiomeDefs.h"

struct ColumnComposition {
	Block_ID surfaceBlock;
	std::vector<std::pair<Block_ID, int>> middleBlocks;
};

class Biome {
public:
	Biome(Biome_ID id, const std::string& name);
	~Biome() = default;
public:
	Biome_ID getID() const;
	const std::string& getName() const;

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
	Biome_ID m_id;
	std::string m_name;

	float m_temperature;
	float m_rainfall;
	BiomeFlags m_flags;
	NoiseProperties m_noiseProperties;
	ColumnComposition m_composition;
};