#include "FullChunkMesh.h"

ChunkMesh* FullChunkMesh::getOrCreateSubMesh(const std::shared_ptr<Material>& material) {
    return &m_chunkMeshes[material];
}

std::vector<ChunkRenderable> FullChunkMesh::getRenderables() {
    std::vector<ChunkRenderable> renderables;

    renderables.reserve(m_chunkMeshes.size());

    for (auto& [material, mesh] : m_chunkMeshes) {
        renderables.push_back({material, mesh.generateChunkVAO()});
    }

    return renderables;
}
