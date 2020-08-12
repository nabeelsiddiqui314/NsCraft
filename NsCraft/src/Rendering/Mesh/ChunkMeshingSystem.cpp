#include "ChunkMeshingSystem.h"
#include "../../World/Chunk/World.h"
#include "../../Math/Vector3.h"
#include "../../World/Events/ChunkLoadEvent.h"
#include "../../Math/Directions.h"
#include "../ChunkRenderer.h"
#include <vector>

ChunkMeshingSystem::ChunkMeshingSystem(const std::shared_ptr<World>& world, const std::shared_ptr<BlockRegistry>& blockRegistry,
	const std::shared_ptr<ChunkRenderer>& renderer)
	: m_world(world), 
	  m_blockRegistry(blockRegistry),
      m_renderer(renderer) {}

void ChunkMeshingSystem::onWorldEvent(const ChunkLoadEvent& event) {
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
			// perform meshing
		}
	}
}

void ChunkMeshingSystem::onWorldEvent(const ChunkUnloadEvent& event) {
	// remove from renderer
}

bool ChunkMeshingSystem::doesChunkHaveAllNeighbors(const Vector3& chunkPosition) const {
	return m_world->doesChunkExist(chunkPosition + Directions::Up) &&
		   m_world->doesChunkExist(chunkPosition + Directions::Down) &&
		   m_world->doesChunkExist(chunkPosition + Directions::Right) && 
		   m_world->doesChunkExist(chunkPosition + Directions::Left) && 
		   m_world->doesChunkExist(chunkPosition + Directions::Front) && 
		   m_world->doesChunkExist(chunkPosition + Directions::Back);
}
