#include "ChunkMeshingSystem.h"

ChunkMeshingSystem::ChunkMeshingSystem(const std::shared_ptr<World>& world, const std::shared_ptr<BlockRegistry>& blockRegistry) 
	: m_world(world), m_blockRegistry(blockRegistry) {}

void ChunkMeshingSystem::onWorldEvent(const ChunkLoadEvent& event) {
	
}

void ChunkMeshingSystem::onWorldEvent(const ChunkUnloadEvent& event) {

}
