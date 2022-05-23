#include "ChunkMeshingSystem.h"
#include "../../World/Chunk/World.h"
#include "../../Math/Vector3.h"
#include "../../World/Events/Events.h"
#include "../../Math/Directions.h"
#include "../ChunkRenderer.h"
#include "FullChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../World/Chunk/Chunk.h"
#include "../../World/Chunk/PaddedChunk.h"
#include "../../BlockRendering/BlockModel/IBlockModel.h"
#include <vector>

ChunkMeshingSystem::ChunkMeshingSystem(const std::shared_ptr<World>& world, ChunkRenderer& renderer)
	: m_world(world),
      m_renderer(renderer),
	  m_meshThreadPool(1)
      {}

void ChunkMeshingSystem::onEvent(const ChunkLoadEvent& event) {
	const auto& chunkPosition = event.chunkPosition;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			for (int z = -1; z <= 1; z++) {
				enqueueChunkToMesh(chunkPosition + Vector3(x, y, z));
			}
		}
	}
}

void ChunkMeshingSystem::onEvent(const ChunkUnloadEvent& event) {
	const auto& chunkPosiiton = event.chunkPosition;
	m_renderer.removeChunk(chunkPosiiton);
}

void ChunkMeshingSystem::onEvent(const ChunkModifyEvent& event) {
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

void ChunkMeshingSystem::generateChunkMeshes() {
	for (auto& chunkPosition : m_chunksToMesh) {
		meshChunk(chunkPosition);
	}

	m_chunksToMesh.clear();
}

void ChunkMeshingSystem::enqueueChunkToMesh(const Vector3& chunkPosition) {
	if (m_world->doesChunkExist(chunkPosition)) {
		for (int x = -1; x <= 1; x++) {
			for (int z = -1; z <= 1; z++) {
				for (int y = -1; y <= 1; y++) {
					Vector3 neighborChunkPosition = chunkPosition + Vector3(x, y, z);

					if (!isChunkPositionValid(neighborChunkPosition)) {
						continue;
					}
					if (!m_world->doesChunkExist(neighborChunkPosition)) {
						return;
					}
				}
			}
		}
		m_chunksToMesh.emplace(chunkPosition);
	}
}

void ChunkMeshingSystem::meshChunk(const Vector3& chunkPosition) {
	if (!m_world->isChunkFullyInvisible(chunkPosition) && !isChunkOccluded(chunkPosition)) { // optimization to prevent unnecessary processing
		PaddedChunk paddedChunk(chunkPosition, *m_world);

		m_meshThreadPool.enqueueTask([this, paddedChunk, chunkPosition]() {
			auto meshes = std::make_shared<FullChunkMesh>();

			auto& blockRegistry = BlockRegistry::getInstance();

			for (int x = 0; x < Chunk::WIDTH; x++) {
				for (int y = 0; y < Chunk::WIDTH; y++) {
					for (int z = 0; z < Chunk::WIDTH; z++) {
						Vector3 blockPosition = { x, y, z };

						ChunkNode currentNode = paddedChunk.getNode(blockPosition);

						const Block& block = blockRegistry.getBlockFromID(currentNode.blockID);

						if (block.isInvisible()) {
							continue;
						}

						auto mesh = meshes->getOrCreateSubMesh(block.getMaterial());

						mesh->setCurrentOrigin(blockPosition);
						block.getBlockModel()->generateMesh(blockPosition, *mesh, paddedChunk);
					}
				}
			}
			m_renderer.enqueueMesh(chunkPosition, meshes);
		});
	}
	else {
		m_renderer.removeChunk(chunkPosition);
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

bool ChunkMeshingSystem::isChunkPositionValid(const Vector3& chunkPosition) {
	return chunkPosition.y >= 0 && chunkPosition.y < m_world->getMaxHeight();
}
