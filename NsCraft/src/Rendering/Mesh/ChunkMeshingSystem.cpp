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

#define BIND_EVENT(function) std::bind(&ChunkMeshingSystem::function, this, std::placeholders::_1)

ChunkMeshingSystem::ChunkMeshingSystem(const std::shared_ptr<World>& world, const BlockRegistry& blockRegistry, const TextureAtlas& textureAtlas, ChunkRenderer& renderer)
	: m_world(world), 
	  m_blockRegistry(blockRegistry),
	  m_textureAtlas(textureAtlas),
      m_renderer(renderer),
	  m_meshThreadPool(1)
      {}

void ChunkMeshingSystem::onEvent(IEvent& event) {
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<ChunkLoadEvent>(BIND_EVENT(onChunkLoad));
	dispatcher.dispatch<ChunkUnloadEvent>(BIND_EVENT(onChunkUnload));
	dispatcher.dispatch<ChunkModifyEvent>(BIND_EVENT(onChunkModify));
}

void ChunkMeshingSystem::onChunkLoad(ChunkLoadEvent& event) const {
	const auto& chunkPosition = event.chunkPosition;

	std::vector<Vector3> chunksToMesh;

	chunksToMesh.emplace_back(chunkPosition + Directions::Up);
	chunksToMesh.emplace_back(chunkPosition + Directions::Down);
	chunksToMesh.emplace_back(chunkPosition + Directions::Right);
	chunksToMesh.emplace_back(chunkPosition + Directions::Left);
	chunksToMesh.emplace_back(chunkPosition + Directions::Front);
	chunksToMesh.emplace_back(chunkPosition + Directions::Back);

	for (const auto& chunk : chunksToMesh) {
		if (m_world->doesChunkExist(chunk) && doesChunkHaveAllNeighbors(chunk)) {
			meshChunk(chunk);
		}
	}
}

void ChunkMeshingSystem::onChunkUnload(ChunkUnloadEvent& event) const {
	const auto& chunkPosiiton = event.chunkPosition;
	m_renderer.removeMesh(chunkPosiiton);
}

void ChunkMeshingSystem::onChunkModify(ChunkModifyEvent& event) const {
	const auto& chunkPosition = event.chunkPosition;
	const auto& blockPosition = event.blockPosition;

  	std::vector<Vector3> chunksToMesh;

	chunksToMesh.emplace_back(chunkPosition);

	// check if the modified block is on the edge of the chunk and if so add that to the list of chunks to be meshed
	if (blockPosition.x == 0) {
		auto chunk = chunkPosition;
		chunk.x -= 1;
		chunksToMesh.emplace_back(chunk);
	}

	if (blockPosition.y == 0) {
		auto chunk = chunkPosition;
		chunk.y -= 1;
		chunksToMesh.emplace_back(chunk);
	}

	if (blockPosition.z == 0) {
		auto chunk = chunkPosition;
		chunk.z -= 1;
		chunksToMesh.emplace_back(chunk);
	}

	if (blockPosition.x == Chunk::WIDTH - 1) {
		auto chunk = chunkPosition;
		chunk.x += 1;
		chunksToMesh.emplace_back(chunk);
	}

	if (blockPosition.y == Chunk::WIDTH - 1) {
		auto chunk = chunkPosition;
		chunk.y += 1;
		chunksToMesh.emplace_back(chunk);
	}

	if (blockPosition.z == Chunk::WIDTH - 1) {
		auto chunk = chunkPosition;
		chunk.z += 1;
		chunksToMesh.emplace_back(chunk);
	}

	for (const auto& chunk : chunksToMesh) {
		if (m_world->doesChunkExist(chunk) && doesChunkHaveAllNeighbors(chunk)) {
			meshChunk(chunk);
		}
	}
}

void ChunkMeshingSystem::meshChunk(const Vector3& chunkPosition) const {
	m_meshThreadPool.enqueueTask([this, chunkPosition]() {
		auto mesh = std::make_shared<ChunkMesh>(m_textureAtlas);

		for (int x = 0; x < Chunk::WIDTH; x++) {
			for (int y = 0; y < Chunk::WIDTH; y++) {
				for (int z = 0; z < Chunk::WIDTH; z++) {
					Vector3 blockPosition = (chunkPosition * Chunk::WIDTH) + Vector3(x, y, z);
					Block_ID blockID = m_world->getBlockIDAt(blockPosition);
					const auto& block = m_blockRegistry.getBlockFromID(blockID);
					block.getMeshGenerator()->generateMesh(*mesh, m_blockRegistry, *m_world, blockPosition);
				}
			}
		}
		if (!mesh->isEmpty()) {
			m_renderer.addMesh(chunkPosition, mesh);
		}
	});
}

bool ChunkMeshingSystem::doesChunkHaveAllNeighbors(const Vector3& chunkPosition) const {
	bool sideNeighbors = m_world->doesChunkExist(chunkPosition + Directions::Right) && 
		                 m_world->doesChunkExist(chunkPosition + Directions::Left) && 
		                 m_world->doesChunkExist(chunkPosition + Directions::Front) && 
		                 m_world->doesChunkExist(chunkPosition + Directions::Back);

	bool topNeighbor = m_world->doesChunkExist(chunkPosition + Directions::Up);
	bool bottomNeighbor = m_world->doesChunkExist(chunkPosition + Directions::Down);

	if (chunkPosition.y == 0) {
		return sideNeighbors && topNeighbor;
	}

	return sideNeighbors && topNeighbor && bottomNeighbor;
}