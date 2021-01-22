#pragma once
#include <vector>
#include "../../Blocks/BlockDefs.h"
#include "../../../Math/SimplexNoise.h"
#include "BiomeDefs.h"

struct BlockLayer {
	BlockLayer() = default;

	// To make it easier to add elements to the initializer list
	BlockLayer(Block_ID _block) : block(_block) {}
	BlockLayer(Block_ID _block, int _height) : block(_block), height(_height) {}

	Block_ID block = 0;
	int height = 1;
};


struct ColumnComposition {
	ColumnComposition() = default;

	// Composition can be set equal to an initializer list due to implicit conversion
	ColumnComposition(const std::initializer_list<BlockLayer>& _layers) : layers(_layers) {}

	std::vector<BlockLayer> layers;
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