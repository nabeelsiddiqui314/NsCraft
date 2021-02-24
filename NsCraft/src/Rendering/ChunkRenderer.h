#pragma once
#include <unordered_map>
#include <memory>
#include <queue>
#include "../Math/Vector3.h"
#include "Mesh/FullChunkMesh.h"

class Frustum;
class VertexArray;
class Material;
class Texture;

class ChunkRenderer {
private:
	typedef std::shared_ptr<VertexArray> VaoPtr;
	typedef std::shared_ptr<FullChunkMesh> FullMeshPtr;
	typedef std::shared_ptr<Material> MaterialPtr;
public:
	ChunkRenderer();
	~ChunkRenderer() = default;
public:
	void enqueueMesh(const Vector3& position, const FullMeshPtr& meshes);
	void removeChunk(const Vector3& position);
	void renderChunks(const Frustum& viewFrustum);
private:
	void loadMeshes();
private:
	std::unordered_map<Vector3, std::vector<ChunkRenderable>> m_renderableChunkMap;
	std::queue<std::pair<Vector3, FullMeshPtr>> m_meshToLoad;
};