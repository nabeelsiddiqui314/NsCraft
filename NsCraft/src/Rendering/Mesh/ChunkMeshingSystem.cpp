#include "ChunkMeshingSystem.h"
#include "../../World/Chunk/World.h"
#include "../../Math/Vector3.h"
#include "../../World/Events/ChunkLoadEvent.h"
#include "../../World/Events/ChunkUnloadEvent.h"
#include "../../Math/Directions.h"
#include "../ChunkRenderer.h"
#include "ChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../World/Chunk/Chunk.h"
#include "IMeshGenerator.h"
#include <vector>
#include "../../EventSystem/EventDispatcher.h"

#define BIND_EVENT(function) std::bind(&ChunkMeshingSystem::function, this, std::placeholders::_1)

ChunkMeshingSystem::ChunkMeshingSystem(const std::shared_ptr<World>& world, const BlockRegistry& blockRegistry, ChunkRenderer& renderer)
	: m_world(world), 
	  m_blockRegistry(blockRegistry),
      m_renderer(renderer) {}

void ChunkMeshingSystem::onEvent(IEvent& event) {
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<ChunkLoadEvent>(BIND_EVENT(onChunkLoad));
	dispatcher.dispatch<ChunkUnloadEvent>(BIND_EVENT(onChunkUnload));
}

void ChunkMeshingSystem::onChunkLoad(ChunkLoadEvent& event) const {
	const auto& chunkPosition = event.chunkPosition;

	std::vector<Vector3> neighbors;

	neighbors.emplace_back(chunkPosition + Directions::Up);
	neighbors.emplace_back(chunkPosition + Directions::Down);
	neighbors.emplace_back(chunkPosition + Directions::Right);
	neighbors.emplace_back(chunkPosition + Directions::Left);
	neighbors.emplace_back(chunkPosition + Directions::Front);
	neighbors.emplace_back(chunkPosition + Directions::Back);

	for (const auto& neighbor : neighbors) {
		if (m_world->doesChunkExist(neighbor) && doesChunkHaveAllNeighbors(neighbor)) {
			ChunkMesh mesh;

			for (int x = 0; x < Chunk::WIDTH; x++) {
				for (int y = 0; y < Chunk::WIDTH; y++) {
					for (int z = 0; z < Chunk::WIDTH; z++) {
						Vector3 blockPosition = (neighbor * Chunk::WIDTH) + Vector3(x, y, z);
						Block_ID blockID = m_world->getBlockIDAt(blockPosition);
						const auto& block = m_blockRegistry.getBlockFromID(blockID);
						block.getMeshGenerator()->generateMesh(mesh, m_blockRegistry, *m_world, blockPosition);
					}
				}
			}
			if (!mesh.isEmpty()) {
				m_renderer.addMesh(neighbor, mesh);
			}
		}
	}
}

void ChunkMeshingSystem::onChunkUnload(ChunkUnloadEvent& event) const {
	const auto& chunkPosiiton = event.chunkPosition;
	m_renderer.removeMesh(chunkPosiiton);
}

bool ChunkMeshingSystem::doesChunkHaveAllNeighbors(const Vector3& chunkPosition) const {
	return m_world->doesChunkExist(chunkPosition + Directions::Up) &&
		   m_world->doesChunkExist(chunkPosition + Directions::Down) &&
		   m_world->doesChunkExist(chunkPosition + Directions::Right) && 
		   m_world->doesChunkExist(chunkPosition + Directions::Left) && 
		   m_world->doesChunkExist(chunkPosition + Directions::Front) && 
		   m_world->doesChunkExist(chunkPosition + Directions::Back);
}
