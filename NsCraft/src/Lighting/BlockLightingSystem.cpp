#include "BlockLightingSystem.h"
#include "../World/Chunk/World.h"
#include "../World/Blocks/BlockRegistry.h"
#include "../World/Events/Events.h"
#include "../World/Blocks/Block.h"
#include "../World/Chunk/Chunk.h"
#include "../Math/Vector2.h"
#include "../Math/CoordinateConversion.h"
#include "../Math/Directions.h"

BlockLightingSystem::BlockLightingSystem(const std::shared_ptr<World>& world)
	: m_world(world), m_lightPropogator(world) {}

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

void BlockLightingSystem::handleNaturalLight(const Vector3& blockPosition, const Block& previousBlock, const Block& newBlock) {
	if (newBlock.getLuminocity() > 0 &&
		previousBlock.getLuminocity() == 0) {
		addNaturalLight(blockPosition, newBlock.getLuminocity());
	}
	else if (newBlock.getLuminocity() == 0 &&
		previousBlock.getLuminocity() > 0) {
		removeNaturalLight(blockPosition);
	}
	else if (newBlock.getLuminocity() == 0 &&
		previousBlock.getLuminocity() == 0) {
		updateNaturalLight(blockPosition);
	}
}

void BlockLightingSystem::addNaturalLight(const Vector3& blockPosition, std::uint8_t luminocity) {
	m_lightPropogator.addNaturalLight(blockPosition, luminocity);
	m_lightPropogator.updateLights();
}

void BlockLightingSystem::removeNaturalLight(const Vector3& blockPosition) {
	m_lightPropogator.removeNaturalLight(blockPosition);
	m_lightPropogator.updateLights();
}

void BlockLightingSystem::updateNaturalLight(const Vector3& blockPosition) {
	removeNaturalLight(blockPosition);

	for (auto& neigborOffset : Directions::List) {
		auto neighborPos = blockPosition + neigborOffset;

		auto& blockRegistry = BlockRegistry::getInstance();
		auto& neigborBlock = blockRegistry.getBlockFromID(m_world->getBlockIDAt(neighborPos));

		if (neigborBlock.getLuminocity() > 0) {
			addNaturalLight(neighborPos, neigborBlock.getLuminocity());
		}
		else {
			removeNaturalLight(neighborPos);
		}
	}
}

void BlockLightingSystem::allowSkyLight(const Vector3& blockPosition) {
	for (auto& neighborOffset : Directions::List) {
		m_lightPropogator.addSkyLight(blockPosition + neighborOffset, m_world->getSkyLightAt(blockPosition + neighborOffset));
		m_lightPropogator.updateLights();
	}
}

void BlockLightingSystem::removeSkyLight(const Vector3& blockPosition) {
	m_lightPropogator.removeSkyLight(blockPosition);
	m_lightPropogator.updateLights();
}

void BlockLightingSystem::filterSkyLight(const Vector3& blockPosition) {
	removeSkyLight(blockPosition);
	allowSkyLight(blockPosition);
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

			m_lightPropogator.addSkyLight(blockPosition + offset, 15);
		}
	}

	m_lightPropogator.updateLights();
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