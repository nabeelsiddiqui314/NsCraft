#include "BlockLightingSystem.h"
#include "../World/Chunk/World.h"
#include "../World/Events/Events.h"
#include "../World/Blocks/BlockRegistry.h"
#include "../World/Blocks/Block.h"
#include "../World/Chunk/Chunk.h"
#include "../Math/Directions.h"

BlockLightingSystem::BlockLightingSystem(const std::shared_ptr<World>& world)
	: m_world(world) {}

void BlockLightingSystem::onEvent(BlockModifyEvent& event) {
	if (m_world->doesChunkHaveAllNeighbors(event.chunkPosition)) {
		auto& blockRegistry = BlockRegistry::getInstance();
		auto& previousBlock = blockRegistry.getBlockFromID(event.previousBlock);
		auto& newBlock = blockRegistry.getBlockFromID(event.newBlock);

		Vector3 blockPosition = event.chunkPosition * Chunk::WIDTH + event.blockPosition;

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
}

void BlockLightingSystem::addLight(const Vector3& blockPosition, std::uint8_t luminocity) {
	m_world->setNaturalLightAt(blockPosition, luminocity);
	m_lightBfsQueue.emplace(blockPosition);

	updatePropogationQueue();
}

void BlockLightingSystem::removeLight(const Vector3& blockPosition) {
	m_lightRemovalBfsQueue.emplace(blockPosition, m_world->getNaturalLightAt(blockPosition));
	m_world->setNaturalLightAt(blockPosition, 0);

	updateRemovalQueue();
	// Block removal might add nodes to the light bfs queue so it needs to be updated as well.
	updatePropogationQueue();
}

void BlockLightingSystem::editBlock(const Vector3& blockPosition) {
	std::vector<Vector3> blocksToProcess;
	blocksToProcess.emplace_back(blockPosition);
	blocksToProcess.emplace_back(blockPosition + Directions::Up);
	blocksToProcess.emplace_back(blockPosition + Directions::Down);
	blocksToProcess.emplace_back(blockPosition + Directions::Left);
	blocksToProcess.emplace_back(blockPosition + Directions::Right);
	blocksToProcess.emplace_back(blockPosition + Directions::Front);
	blocksToProcess.emplace_back(blockPosition + Directions::Back);

	for (auto& blockPos : blocksToProcess) {
		auto& blockRegistry = BlockRegistry::getInstance();
		auto& block = blockRegistry.getBlockFromID(m_world->getBlockIDAt(blockPos));
		if (block.getLuminocity() > 0) {
			addLight(blockPos, block.getLuminocity());
			continue;
		}

		if (m_world->getNaturalLightAt(blockPos) > 0) {
			removeLight(blockPos);
			continue;
		}
	}
}

void BlockLightingSystem::updatePropogationQueue() {
	auto spreadToNeighbor = [this](const Vector3& neighborPos, std::uint8_t lightValue) {
		auto& blockRegistry = BlockRegistry::getInstance();
		auto& neighborBlock = blockRegistry.getBlockFromID(m_world->getBlockIDAt(neighborPos));
		if (!neighborBlock.isCompletelyOpaque() &&
			m_world->getNaturalLightAt(neighborPos) + neighborBlock.getOpacity() + 2 <= lightValue) {
			m_world->setNaturalLightAt(neighborPos, lightValue - neighborBlock.getOpacity() - 1);
			m_lightBfsQueue.emplace(neighborPos);
		}
	};

	while (!m_lightBfsQueue.empty()) {
		auto blockPosition = m_lightBfsQueue.front();
		std::uint8_t lightValue = m_world->getNaturalLightAt(blockPosition);
		m_lightBfsQueue.pop();

		spreadToNeighbor(blockPosition + Directions::Up, lightValue);
		spreadToNeighbor(blockPosition + Directions::Down, lightValue);
		spreadToNeighbor(blockPosition + Directions::Left, lightValue);
		spreadToNeighbor(blockPosition + Directions::Right, lightValue);
		spreadToNeighbor(blockPosition + Directions::Front, lightValue);
		spreadToNeighbor(blockPosition + Directions::Back, lightValue);
	}
}

void BlockLightingSystem::updateRemovalQueue() {
	auto spreadLightRemoval = [this](const Vector3& neighborPos, std::uint8_t lightValue) {
		std::uint8_t neighborLightValue = m_world->getNaturalLightAt(neighborPos);

		if (neighborLightValue != 0 && neighborLightValue < lightValue) {
			m_world->setNaturalLightAt(neighborPos, 0);
			m_lightRemovalBfsQueue.emplace(neighborPos, neighborLightValue);
		}
		else if (neighborLightValue >= lightValue) {
			m_lightBfsQueue.emplace(neighborPos);
		}
	};

	while (!m_lightRemovalBfsQueue.empty()) {
		auto& lightRemovalNode = m_lightRemovalBfsQueue.front();
		auto blockPosition = lightRemovalNode.position;
		std::uint8_t lightValue = lightRemovalNode.value;
		m_lightRemovalBfsQueue.pop();

		spreadLightRemoval(blockPosition + Directions::Up, lightValue);
		spreadLightRemoval(blockPosition + Directions::Down, lightValue);
		spreadLightRemoval(blockPosition + Directions::Left, lightValue);
		spreadLightRemoval(blockPosition + Directions::Right, lightValue);
		spreadLightRemoval(blockPosition + Directions::Front, lightValue);
		spreadLightRemoval(blockPosition + Directions::Back, lightValue);
	}
}