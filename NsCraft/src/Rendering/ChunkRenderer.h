#pragma once
#include <unordered_map>
#include <memory>
#include <queue>
#include "../Math/Vector3.h"

class Frustum;
class ChunkMesh;
class VertexArray;
class Material;
class Texture;

class ChunkRenderer {
private:
	typedef std::shared_ptr<VertexArray> VaoPtr;
	typedef std::shared_ptr<ChunkMesh> ChunkMeshPtr;
	typedef std::shared_ptr<Material> MaterialPtr;
public:
	ChunkRenderer(const std::shared_ptr<Texture>& texture);
	~ChunkRenderer() = default;
public:
	void addMesh(const Vector3& position, const ChunkMeshPtr& mesh);
	void removeMesh(const Vector3& position);
	void renderChunks(const Frustum& viewFrustum);
private:
	void loadMeshes();
private:
	std::unordered_map<Vector3, VaoPtr> m_renderableChunkMap;
	std::queue<std::pair<Vector3, ChunkMeshPtr>> m_meshToLoad;
	MaterialPtr m_chunkMaterial;
};