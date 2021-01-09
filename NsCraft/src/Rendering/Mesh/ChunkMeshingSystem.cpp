#include "ChunkMeshingSystem.h"
#include "../../World/Chunk/World.h"
#include "../../Math/Vector3.h"
#include "../../World/Events/ChunkLoadEvent.h"
#include "../../World/Events/ChunkUnloadEvent.h"
#include "../../World/Events/ChunkModifyEvent.h"
#include "../../Math/Directions.h"
#include "../ChunkRenderer.h"
#include "ChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../World/Chunk/Chunk.h"
#include "IMeshGenerator.h"
#include <vector>
#include "../../EventSystem/EventDispatcher.h"

ChunkMeshingSystem::ChunkMeshingSystem(const std::shared_ptr<World>& world, const TextureAtlas& textureAtlas, ChunkRenderer& renderer)
	: m_world(world), 
	  m_textureAtlas(textureAtlas),
      m_renderer(renderer),
	  m_meshThreadPool(1)
      {}

void ChunkMeshingSystem::onEvent(IEvent& event) {
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<ChunkLoadEvent>(BIND_EVENT(ChunkMeshingSystem::onChunkLoad));
	dispatcher.dispatch<ChunkUnloadEvent>(BIND_EVENT(ChunkMeshingSystem::onChunkUnload));
	dispatcher.dispatch<ChunkModifyEvent>(BIND_EVENT(ChunkMeshingSystem::onChunkModify));
}

void ChunkMeshingSystem::generateChunkMeshes() {
	for (auto& chunkPosition : m_chunksToMesh) {
		meshChunk(chunkPosition);
	}

	m_chunksToMesh.clear();
}

void ChunkMeshingSystem::onChunkLoad(ChunkLoadEvent& event) {
	const auto& chunkPosition = event.chunkPosition;

	enqueueChunkToMesh(chunkPosition + Directions::Up);
	enqueueChunkToMesh(chunkPosition + Directions::Down);
	enqueueChunkToMesh(chunkPosition + Directions::Right);
	enqueueChunkToMesh(chunkPosition + Directions::Left);
	enqueueChunkToMesh(chunkPosition + Directions::Front);
	enqueueChunkToMesh(chunkPosition + Directions::Back);
}

void ChunkMeshingSystem::onChunkUnload(ChunkUnloadEvent& event) const {
	const auto& chunkPosiiton = event.chunkPosition;
	m_renderer.removeMesh(chunkPosiiton);
}

void ChunkMeshingSystem::onChunkModify(ChunkModifyEvent& event) {
	const auto& chunkPosition = event.chunkPosition;
	const auto& blockPosition = event.blockPosition;

	enqueueChunkToMesh(chunkPosition);

	// check if the modified block is on the edge of the chunk and if so add that to the list of chunks to be meshed
	if (blockPosition.x == 0) {
		auto chunk = chunkPosition;
		chunk.x -= 1;
		enqueueChunkToMesh(chunk);
	}

	if (blockPosition.y == 0) {
		auto chunk = chunkPosition;
		chunk.y -= 1;
		enqueueChunkToMesh(chunk);
	}

	if (blockPosition.z == 0) {
		auto chunk = chunkPosition;
		chunk.z -= 1;
		enqueueChunkToMesh(chunk);
	}

	if (blockPosition.x == Chunk::WIDTH - 1) {
		auto chunk = chunkPosition;
		chunk.x += 1;
		enqueueChunkToMesh(chunk);
	}

	if (blockPosition.y == Chunk::WIDTH - 1) {
		auto chunk = chunkPosition;
		chunk.y += 1;
		enqueueChunkToMesh(chunk);
	}

	if (blockPosition.z == Chunk::WIDTH - 1) {
		auto chunk = chunkPosition;
		chunk.z += 1;
		enqueueChunkToMesh(chunk);
	}
}

void ChunkMeshingSystem::enqueueChunkToMesh(const Vector3& chunkPosition) {
	if (m_world->doesChunkExist(chunkPosition) && m_world->doesChunkHaveAllNeighbors(chunkPosition)) {
		m_chunksToMesh.emplace(chunkPosition);
	}
}

void ChunkMeshingSystem::meshChunk(const Vector3& chunkPosition) {
	if (m_world->isChunkFullyOpaque(chunkPosition) &&
		m_world->isChunkFullyOpaque(chunkPosition + Directions::Up) &&
		m_world->isChunkFullyOpaque(chunkPosition + Directions::Down) &&
		m_world->isChunkFullyOpaque(chunkPosition + Directions::Left) &&
		m_world->isChunkFullyOpaque(chunkPosition + Directions::Right) &&
		m_world->isChunkFullyOpaque(chunkPosition + Directions::Front) &&
		m_world->isChunkFullyOpaque(chunkPosition + Directions::Back)) {
		return;
	}

	m_meshThreadPool.enqueueTask([this, chunkPosition]() {
		auto mesh = std::make_shared<ChunkMesh>(m_textureAtlas);

		auto& blockRegistry = BlockRegistry::getInstance();

		for (int x = 0; x < Chunk::WIDTH; x++) {
			for (int y = 0; y < Chunk::WIDTH; y++) {
				for (int z = 0; z < Chunk::WIDTH; z++) {
					Vector3 blockPosition = { x, y, z };
					Block_ID blockID = m_world->getBlockIDAt((chunkPosition * Chunk::WIDTH) + blockPosition);
					const auto& block = blockRegistry.getBlockFromID(blockID);
					block.getMeshGenerator()->generateMesh(*mesh, *m_world, chunkPosition, blockPosition);
				}
			}
		}
		if (!mesh->isEmpty()) {
			m_renderer.addMesh(chunkPosition, mesh);
		}
	});
}