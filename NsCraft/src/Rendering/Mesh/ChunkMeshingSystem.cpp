#include "ChunkMeshingSystem.h"
#include "../../World/Chunk/World.h"
#include "../../Math/Vector3.h"
#include "../../World/Events/ChunkLoadEvent.h"
#include "../../World/Events/ChunkUnloadEvent.h"
#include "../../World/Events/ChunkModifyEvent.h"
#include "../../Math/Directions.h"
#include "../ChunkRenderer.h"
#include "FullChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../World/Chunk/Chunk.h"
#include "../../World/Chunk/PaddedChunk.h"
#include "IMeshGenerator.h"
#include <vector>
#include "../../EventSystem/EventDispatcher.h"

ChunkMeshingSystem::ChunkMeshingSystem(const std::shared_ptr<World>& world, ChunkRenderer& renderer)
	: m_world(world),
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
	if (!m_world->isChunkFullyInvisible(chunkPosition) && !isChunkOccluded(chunkPosition)) { // optimization to prevent unnecessary processing
		ChunkNeighborhood chunkNeighborhood;

		chunkNeighborhood.centre = m_world->getChunk(chunkPosition);
		chunkNeighborhood.top = m_world->getChunk(chunkPosition + Directions::Up);
		chunkNeighborhood.bottom = m_world->getChunk(chunkPosition + Directions::Down);
		chunkNeighborhood.left = m_world->getChunk(chunkPosition + Directions::Left);
		chunkNeighborhood.right = m_world->getChunk(chunkPosition + Directions::Right);
		chunkNeighborhood.front = m_world->getChunk(chunkPosition + Directions::Front);
		chunkNeighborhood.back = m_world->getChunk(chunkPosition + Directions::Back);

		PaddedChunk paddedChunk(chunkNeighborhood);

		m_meshThreadPool.enqueueTask([this, paddedChunk, chunkPosition]() {
			auto meshes = std::make_shared<FullChunkMesh>();

			auto& blockRegistry = BlockRegistry::getInstance();

			for (int x = 0; x < Chunk::WIDTH; x++) {
				for (int y = 0; y < Chunk::WIDTH; y++) {
					for (int z = 0; z < Chunk::WIDTH; z++) {
						Vector3 blockPosition = { x, y, z };

						ChunkNode currentNode = paddedChunk.getNode(blockPosition);

						const Block& block = blockRegistry.getBlockFromID(currentNode.getBlockID());

						if (block.isInvisible()) {
							continue;
						}

						Neighborhood neighborhood;
						neighborhood.centre = currentNode;
						neighborhood.top = paddedChunk.getNode(blockPosition + Directions::Up);
						neighborhood.bottom = paddedChunk.getNode(blockPosition + Directions::Down);
						neighborhood.front = paddedChunk.getNode(blockPosition + Directions::Front);
						neighborhood.back = paddedChunk.getNode(blockPosition + Directions::Back);
						neighborhood.left = paddedChunk.getNode(blockPosition + Directions::Left);
						neighborhood.right = paddedChunk.getNode(blockPosition + Directions::Right);

						auto mesh = meshes->getOrCreateSubMesh(block.getMaterial());

						mesh->setCurrentOrigin(blockPosition);
						block.getMeshGenerator()->generateMesh(*mesh, neighborhood);
					}
				}
			}
			m_renderer.addMesh(chunkPosition, meshes);
		});
	}
	else {
		m_renderer.removeMesh(chunkPosition);
	}
}

bool ChunkMeshingSystem::isChunkOccluded(const Vector3& position) {
	return m_world->isChunkFullyOpaque(position) &&
		   m_world->isChunkFullyOpaque(position + Directions::Up) &&
		   m_world->isChunkFullyOpaque(position + Directions::Down) &&
		   m_world->isChunkFullyOpaque(position + Directions::Left) &&
		   m_world->isChunkFullyOpaque(position + Directions::Right) &&
		   m_world->isChunkFullyOpaque(position + Directions::Front) &&
		   m_world->isChunkFullyOpaque(position + Directions::Back);
}
