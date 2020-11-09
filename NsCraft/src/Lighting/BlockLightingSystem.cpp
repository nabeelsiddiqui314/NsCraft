#include "BlockLightingSystem.h"
#include "../EventSystem/EventDispatcher.h"
#include "../World/Chunk/World.h"
#include "../World/Events/BlockModifiedEvent.h"
#include "../World/Blocks/BlockRegistry.h"
#include "../World/Blocks/Block.h"
#include "../World/Chunk/Chunk.h"
#include "../Math/Directions.h"

BlockLightingSystem::BlockLightingSystem(const std::shared_ptr<World>& world)
	: m_world(world) {}

void BlockLightingSystem::onEvent(IEvent& event) {
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<BlockModifiedEvent>(BIND_EVENT(BlockLightingSystem::onBlockModified));
}

void BlockLightingSystem::onBlockModified(BlockModifiedEvent& event) {
	if (doesChunkHaveAllNeighbors(event.chunkPosition)) {
		auto& blockRegistry = BlockRegistry::getInstance();
		auto& previousBlock = blockRegistry.getBlockFromID(event.previousBlock);
		auto& newBlock = blockRegistry.getBlockFromID(event.newBlock);

		if (newBlock.getLuminocity() > 0 &&
			previousBlock.getLuminocity() != newBlock.getLuminocity()) {
			propogateLight(event.chunkPosition * Chunk::WIDTH + event.blockPosition, newBlock.getLuminocity());
		}
	}
}

void BlockLightingSystem::propogateLight(const Vector3& startBlockPosition, std::uint8_t luminocity) {
	m_world->setNaturalLightAt(startBlockPosition, luminocity);
	m_lightBfsQueue.emplace(startBlockPosition);

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

void BlockLightingSystem::spreadToNeighbor(const Vector3& neighborPos, std::uint8_t lightValue) {
	auto& blockRegistry = BlockRegistry::getInstance();
	auto& neighborBlock = blockRegistry.getBlockFromID(m_world->getBlockIDAt(neighborPos));
	if (!neighborBlock.isOpaque() &&
		m_world->getNaturalLightAt(neighborPos) + 2 <= lightValue) {
		m_world->setNaturalLightAt(neighborPos, lightValue - 1);
		m_lightBfsQueue.emplace(neighborPos);
	}
}

bool BlockLightingSystem::doesChunkHaveAllNeighbors(const Vector3& chunkPosition) {
	return m_world->doesChunkExist(chunkPosition + Directions::Up) &&
		m_world->doesChunkExist(chunkPosition + Directions::Down)&&
		m_world->doesChunkExist(chunkPosition + Directions::Left)&&
		m_world->doesChunkExist(chunkPosition + Directions::Right)&&
		m_world->doesChunkExist(chunkPosition + Directions::Front)&&
		m_world->doesChunkExist(chunkPosition + Directions::Back);
}
