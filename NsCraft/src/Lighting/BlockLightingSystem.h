#pragma once
#include <memory>
#include <queue>
#include "../World/Events/IWorldObserver.h"
#include "../Math/Vector3.h"

class World;
struct Vector3;
class Block;

class BlockLightingSystem : public IWorldObserver {
private:
	struct LightRemovalNode {
		LightRemovalNode(const Vector3& _position, std::uint8_t _value) 
			: position(_position),
		      value(_value) {}

		Vector3 position;
		std::uint8_t value;
	};
public:
	BlockLightingSystem(const std::shared_ptr<World>& world);
	~BlockLightingSystem() = default;
public:
	void onEvent(const BlockModifyEvent& event) override;
private:
	void handleNaturalLight(const Vector3& blockPosition, const Block& previousBlock, const Block& newBlock);
	void handleSkyLight(const Vector3& blockPosition, const Block& block);

	void addLight(const Vector3& blockPosition, std::uint8_t luminocity);
	void removeLight(const Vector3& blockPosition);
	void editBlock(const Vector3& blockPosition);

	void allowSkyLight(const Vector3& blockPosition);
	void removeSkyLight(const Vector3& blockPosition);
	void filterSkyLight(const Vector3& blockPosition);

	void updateNaturalLightPropogation();
	void updateNaturalLightRemoval();

	void updateSkyLightPropopgation();
	void updateSkyLightRemoval();
private:
	std::shared_ptr<World> m_world;

	std::queue<Vector3> m_lightBfsQueue;
	std::queue<LightRemovalNode> m_lightRemovalBfsQueue;

	std::queue<Vector3> m_skyLightBfsQueue;
	std::queue<LightRemovalNode> m_skyLightRemovalBfsQueue;
};