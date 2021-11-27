#pragma once
#include <memory>
#include <queue>
#include "../Math/Vector3.h"

class World;
struct Vector2;
class Block;

class LightPropogator {
private:
	struct LightRemovalNode {
		LightRemovalNode(const Vector3& _position, std::uint8_t _value)
			: position(_position),
			value(_value) {}

		Vector3 position;
		std::uint8_t value;
	};
public:
	LightPropogator(const std::shared_ptr<World>& world);
	~LightPropogator() = default;
public:
	void addNaturalLight(const Vector3& blockPosition, std::uint8_t luminocity);
	void addSkyLight(const Vector3& blockPosition, std::uint8_t value);

	void removeNaturalLight(const Vector3& blockPosition);
	void removeSkyLight(const Vector3& blockPosition);

	void updateLights();
private:
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