#pragma once
#include <memory>
#include "../World/Events/IWorldObserver.h"
#include "LightPropogator.h"

class World;
struct Vector2;

class BlockLightingSystem : public IWorldObserver {
public:
	BlockLightingSystem(const std::shared_ptr<World>& world);
	~BlockLightingSystem() = default;
public:
	void onEvent(const ChunkLoadEvent& event) override;
	void onEvent(const BlockModifyEvent& event) override;
private:
	void handleSkyLight(const Vector3& blockPosition, const Block& block);
	void handleNaturalLight(const Vector3& blockPosition, const Block& previousBlock, const Block& newBlock);

	void addNaturalLight(const Vector3& blockPosition, std::uint8_t luminocity);
	void removeNaturalLight(const Vector3& blockPosition);
	void updateNaturalLight(const Vector3& blockPosition);
	
	void allowSkyLight(const Vector3& blockPosition);
	void removeSkyLight(const Vector3& blockPosition);
	void filterSkyLight(const Vector3& blockPosition);

	void lightColumn(const Vector2& columnPosition);

	bool hasColumnGenerated(const Vector2& columnPosition) const;
	bool haveNeighborsGenerated(const Vector2& columnPosition) const;
private:
	std::shared_ptr<World> m_world;
	LightPropogator m_lightPropogator;
};