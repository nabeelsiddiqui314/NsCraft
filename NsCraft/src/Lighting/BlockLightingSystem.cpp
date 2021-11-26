#include "BlockLightingSystem.h"
#include "../World/Chunk/World.h"
#include "../World/Events/Events.h"
#include "../World/Blocks/BlockRegistry.h"
#include "../World/Blocks/Block.h"
#include "../World/Chunk/Chunk.h"
#include "../Math/Directions.h"
#include "../Math/CoordinateConversion.h"
#include "LightDefs.h"

BlockLightingSystem::BlockLightingSystem(const std::shared_ptr<World>& world)
	: m_world(world) {}

void BlockLightingSystem::onEvent(const ChunkLoadEvent& event) {
	for (int x = -1; x <= 1; x++) {
		for (int z= -1; z <= 1; z++) {
			Vector2 columnPosition = { event.chunkPosition.x + x, event.chunkPosition.z + z };

			if (hasColumnGenerated(columnPosition) && haveNeighborsGenerated(columnPosition)) {
				lightColumn(columnPosition);
			}
		}
	}
}

void BlockLightingSystem::onEvent(const BlockModifyEvent& event) {
	if (m_world->doesChunkHaveAllNeighbors(event.chunkPosition)) {
		auto& blockRegistry = BlockRegistry::getInstance();

		auto& previousBlock = blockRegistry.getBlockFromID(event.previousBlock);
		auto& newBlock = blockRegistry.getBlockFromID(event.newBlock);

		Vector3 blockPosition = CoordinateConversion::chunkToWorld(event.chunkPosition, event.blockPosition, Chunk::WIDTH);

		handleNaturalLight(blockPosition, previousBlock, newBlock);
		handleSkyLight(blockPosition, newBlock);
	}
}

void BlockLightingSystem::handleNaturalLight(const Vector3& blockPosition, const Block& previousBlock, const Block& newBlock) {
	if (newBlock.getLuminocity() > 0 &&
		previousBlock.getLuminocity() == 0) {
		addLight(blockPosition, newBlock.getLuminocity());
	}
	else if (newBlock.getLuminocity() == 0 &&
		previousBlock.getLuminocity() > 0) {
		removeLight(blockPosition);
	}
	else if (newBlock.getLuminocity() == 0 &&
		previousBlock.getLuminocity() == 0) {
		editBlock(blockPosition);
	}
}

void BlockLightingSystem::handleSkyLight(const Vector3& blockPosition, const Block& block) {
	if (m_world->getSkyLightAt(blockPosition) > 0) {
		if (block.isCompletelyOpaque()) {
			removeSkyLight(blockPosition);
		}
		else if (block.getOpacity() > 0) {
			filterSkyLight(blockPosition);
		}
		else {
			allowSkyLight(blockPosition);
		}
	}
	else if (block.getOpacity() == 0) {
		allowSkyLight(blockPosition);
	}
}

void BlockLightingSystem::addLight(const Vector3& blockPosition, std::uint8_t luminocity) {
	m_world->setNaturalLightAt(blockPosition, luminocity);
	m_lightBfsQueue.emplace(blockPosition);

	updateNaturalLightPropogation();
}

void BlockLightingSystem::removeLight(const Vector3& blockPosition) {
	m_lightRemovalBfsQueue.emplace(blockPosition, m_world->getNaturalLightAt(blockPosition));
	m_world->setNaturalLightAt(blockPosition, 0);

	updateNaturalLightRemoval();
	// Block removal might add nodes to the light bfs queue so it needs to be updated as well.
	updateNaturalLightPropogation();
}

void BlockLightingSystem::editBlock(const Vector3& blockPosition) {
	removeLight(blockPosition);

	for (auto& neigborOffset : Directions::List) {
		auto neighborPos = blockPosition + neigborOffset;

		auto& blockRegistry = BlockRegistry::getInstance();
		auto& neigborBlock = blockRegistry.getBlockFromID(m_world->getBlockIDAt(neighborPos));

		if (neigborBlock.getLuminocity() > 0) {
			addLight(neighborPos, neigborBlock.getLuminocity());
		}
		else {
			removeLight(neighborPos);
		}
	}
}

void BlockLightingSystem::allowSkyLight(const Vector3& blockPosition) {
	for (auto& neighborOffset : Directions::List) {
		m_world->setSkyLightAt(blockPosition + neighborOffset, m_world->getSkyLightAt(blockPosition + neighborOffset));
		m_skyLightBfsQueue.emplace(blockPosition + neighborOffset);

		updateSkyLightPropopgation();
	}
}

void BlockLightingSystem::removeSkyLight(const Vector3& blockPosition) {
	m_skyLightRemovalBfsQueue.emplace(blockPosition, m_world->getSkyLightAt(blockPosition));
	m_world->setSkyLightAt(blockPosition, 0);

	updateSkyLightRemoval();
	updateSkyLightPropopgation();
}

void BlockLightingSystem::filterSkyLight(const Vector3& blockPosition) {
	removeSkyLight(blockPosition);
	allowSkyLight(blockPosition);
}

void BlockLightingSystem::updateNaturalLightPropogation() {
	while (!m_lightBfsQueue.empty()) {
		auto blockPosition = m_lightBfsQueue.front();
		std::uint8_t lightValue = m_world->getNaturalLightAt(blockPosition);
		m_lightBfsQueue.pop();

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

void BlockLightingSystem::updateNaturalLightRemoval() {
	while (!m_lightRemovalBfsQueue.empty()) {
		auto& lightRemovalNode = m_lightRemovalBfsQueue.front();
		auto blockPosition = lightRemovalNode.position;
		std::uint8_t lightValue = lightRemovalNode.value;
		m_lightRemovalBfsQueue.pop();

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

void BlockLightingSystem::updateSkyLightPropopgation() {
	while (!m_skyLightBfsQueue.empty()) {
		auto blockPosition = m_skyLightBfsQueue.front();
		std::uint8_t lightValue = m_world->getSkyLightAt(blockPosition);
		m_skyLightBfsQueue.pop();

		if (blockPosition.y >= m_world->getMaxHeight() * Chunk::WIDTH) {
			continue;
		}

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

void BlockLightingSystem::updateSkyLightRemoval() {
	while (!m_skyLightRemovalBfsQueue.empty()) {
		auto& lightRemovalNode = m_skyLightRemovalBfsQueue.front();

		auto blockPosition = lightRemovalNode.position;
		std::uint8_t lightValue = lightRemovalNode.value;

		m_skyLightRemovalBfsQueue.pop();

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

void BlockLightingSystem::lightColumn(const Vector2& columnPosition) {
	Vector3 lowestEmptyChunkPosition;

	for (int y = m_world->getMaxHeight() - 1; y >= 0; y--) {
		Vector3 chunkPosition = { columnPosition.x, y, columnPosition.y };

		if (!m_world->isChunkFullyInvisible(chunkPosition)) {
			chunkPosition.y++;
			lowestEmptyChunkPosition = chunkPosition;
			break;
		}
		else {
			m_world->fillChunkWithSkyLight(chunkPosition, 15);
		}
	}

	Vector3 blockPosition = CoordinateConversion::chunkToWorld(lowestEmptyChunkPosition, {0, 0, 0}, Chunk::WIDTH);

	for (int x = 0; x < Chunk::WIDTH; x++) {
		for (int z = 0; z < Chunk::WIDTH; z++) {
			Vector3 offset = {x, 0, z};

			m_world->setSkyLightAt(blockPosition + offset, 15);
			m_skyLightBfsQueue.emplace(blockPosition + offset);
		}
	}

	updateSkyLightPropopgation();
}

bool BlockLightingSystem::hasColumnGenerated(const Vector2& columnPosition) const {
	for (int y = 0; y < m_world->getMaxHeight(); y++) {
		if (!m_world->doesChunkExist({ columnPosition.x, y, columnPosition.y })) {
			return false;
		}
	}

	return true;
}

bool BlockLightingSystem::haveNeighborsGenerated(const Vector2& columnPosition) const {
	for (int x = -1; x <= 1; x++) {
		for (int z = -1; z <= 1; z++) {
			if (!hasColumnGenerated({ columnPosition.x + x, columnPosition.y + z })) {
				return false;
			}
		}
	}

	return true;
}