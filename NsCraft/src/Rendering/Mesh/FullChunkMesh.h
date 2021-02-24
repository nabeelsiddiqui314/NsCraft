#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "ChunkMesh.h"

class VertexArray;
class Material;

struct ChunkRenderable {
	std::shared_ptr<Material> material;
	std::shared_ptr<VertexArray> vao;
};

class FullChunkMesh {
public:
	FullChunkMesh() = default;
	~FullChunkMesh() = default;
public:
	ChunkMesh* getOrCreateSubMesh(const std::shared_ptr<Material>& material);
	std::vector<ChunkRenderable> getRenderables();
private:
	std::unordered_map<std::shared_ptr<Material>, ChunkMesh> m_chunkMeshes;
};