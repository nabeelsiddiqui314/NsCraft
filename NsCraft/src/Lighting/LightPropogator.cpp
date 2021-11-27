#include "LightPropogator.h"
#include "../World/Chunk/World.h"
#include "../World/Blocks/BlockRegistry.h"
#include "../World/Blocks/Block.h"
#include "../World/Chunk/Chunk.h"
#include "../Math/Directions.h"
#include "LightDefs.h"

LightPropogator::LightPropogator(const std::shared_ptr<World>& world) 
	: m_world(world) {}

void LightPropogator::addNaturalLight(const Vector3& blockPosition, std::uint8_t luminocity) {
	m_world->setNaturalLightAt(blockPosition, luminocity);
	m_lightBfsQueue.emplace(blockPosition);
}

void LightPropogator::addSkyLight(const Vector3& blockPosition, std::uint8_t value) {
	m_world->setSkyLightAt(blockPosition, value);
	m_skyLightBfsQueue.emplace(blockPosition);
}

void LightPropogator::removeNaturalLight(const Vector3& blockPosition) {
	m_lightRemovalBfsQueue.emplace(blockPosition, m_world->getNaturalLightAt(blockPosition));
	m_world->setNaturalLightAt(blockPosition, 0);
}

void LightPropogator::removeSkyLight(const Vector3& blockPosition) {
	m_skyLightRemovalBfsQueue.emplace(blockPosition, m_world->getSkyLightAt(blockPosition));
	m_world->setSkyLightAt(blockPosition, 0);
}

void LightPropogator::updateLights() {
	updateNaturalLightRemoval();
	updateNaturalLightPropogation();

	updateSkyLightRemoval();
	updateSkyLightPropopgation();
}

void LightPropogator::updateNaturalLightPropogation() {
	while (!m_lightBfsQueue.empty()) {
		auto blockPosition = m_lightBfsQueue.front();
		std::uint8_t lightValue = m_world->getNaturalLightAt(blockPosition);

		m_lightBfsQueue.pop();

		if (isBlockPositionOutOfBounds(blockPosition))
			continue;

		for (auto& neighborOffset : Directions::List) {
			auto neighborPos = blockPosition + neighborOffset;

			auto& blockRegistry = BlockRegistry::getInstance();
			auto& neighborBlock = blockRegistry.getBlockFromID(m_world->getBlockIDAt(neighborPos));

			if (!neighborBlock.isCompletelyOpaque() &&
				m_world->getNaturalLightAt(neighborPos) + neighborBlock.getOpacity() + 2 <= lightValue) {
				m_world->setNaturalLightAt(neighborPos, lightValue - neighborBlock.getOpacity() - 1);
				m_lightBfsQueue.emplace(neighborPos);
			}
		}
	}
}

void LightPropogator::updateNaturalLightRemoval() {
	while (!m_lightRemovalBfsQueue.empty()) {
		auto& lightRemovalNode = m_lightRemovalBfsQueue.front();

		auto blockPosition = lightRemovalNode.position;
		std::uint8_t lightValue = lightRemovalNode.value;

		m_lightRemovalBfsQueue.pop();

		if (isBlockPositionOutOfBounds(blockPosition))
			continue;

		for (auto& neighborOffset : Directions::List) {
			auto neighborPos = blockPosition + neighborOffset;

			std::uint8_t neighborLightValue = m_world->getNaturalLightAt(neighborPos);

			if (neighborLightValue != 0 && neighborLightValue < lightValue) {
				m_world->setNaturalLightAt(neighborPos, 0);
				m_lightRemovalBfsQueue.emplace(neighborPos, neighborLightValue);
			}
			else if (neighborLightValue >= lightValue) {
				m_lightBfsQueue.emplace(neighborPos);
			}
		}
	}
}

void LightPropogator::updateSkyLightPropopgation() {
	while (!m_skyLightBfsQueue.empty()) {
		auto blockPosition = m_skyLightBfsQueue.front();
		std::uint8_t lightValue = m_world->getSkyLightAt(blockPosition);

		m_skyLightBfsQueue.pop();

		if (isBlockPositionOutOfBounds(blockPosition))
			continue;

		for (auto& neighborOffset : Directions::List) {
			auto neighborPos = blockPosition + neighborOffset;

			auto& blockRegistry = BlockRegistry::getInstance();
			auto& neighborBlock = blockRegistry.getBlockFromID(m_world->getBlockIDAt(neighborPos));

			if (!neighborBlock.isCompletelyOpaque()) {
				if (lightValue == 15 && neighborOffset == Directions::Down) {
					m_world->setSkyLightAt(neighborPos, lightValue - neighborBlock.getOpacity());
					m_skyLightBfsQueue.emplace(neighborPos);
				}
				else if (m_world->getSkyLightAt(neighborPos) + neighborBlock.getOpacity() + 2 <= lightValue) {
					m_world->setSkyLightAt(neighborPos, lightValue - neighborBlock.getOpacity() - 1);
					m_skyLightBfsQueue.emplace(neighborPos);
				}
			}
		}
	}
}

void LightPropogator::updateSkyLightRemoval() {
	while (!m_skyLightRemovalBfsQueue.empty()) {
		auto& lightRemovalNode = m_skyLightRemovalBfsQueue.front();

		auto blockPosition = lightRemovalNode.position;
		std::uint8_t lightValue = lightRemovalNode.value;

		m_skyLightRemovalBfsQueue.pop();

		if (isBlockPositionOutOfBounds(blockPosition))
			continue;

		for (auto& neighborOffset : Directions::List) {
			auto neighborPos = blockPosition + neighborOffset;

			std::uint8_t neighborLightValue = m_world->getSkyLightAt(neighborPos);

			if ((neighborLightValue != 0 && neighborLightValue < lightValue) || (lightValue == 15 && neighborOffset == Directions::Down)) {
				m_world->setSkyLightAt(neighborPos, 0);
				m_skyLightRemovalBfsQueue.emplace(neighborPos, neighborLightValue);
			}
			else if (neighborLightValue >= lightValue) {
				m_skyLightBfsQueue.emplace(neighborPos);
			}
		}
	}
}

bool LightPropogator::isBlockPositionOutOfBounds(const Vector3& blockPosition) const {
	return blockPosition.y < 0 || blockPosition.y >= m_world->getMaxHeight() * Chunk::WIDTH;
}
