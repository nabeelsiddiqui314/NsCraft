#pragma once
#include <unordered_map>
#include <memory>
#include <queue>
#include "../Math/Vector3.h"

#include "../OpenGL/Texture.h"
#include "../OpenGL/Shader.h"

class Camera;
class VertexArray;
class ChunkMesh;

class ChunkRenderer {
private:
	typedef std::shared_ptr<VertexArray> VaoPtr;
	typedef std::shared_ptr<ChunkMesh> ChunkMeshPtr;
public:
	ChunkRenderer();
	~ChunkRenderer() = default;
public:
	void addMesh(const Vector3& position, const ChunkMeshPtr& mesh);
	void removeMesh(const Vector3& position);
	void renderChunks(const Camera& camera);
private:
	void loadMeshes();
private:
	std::unordered_map<Vector3, VaoPtr> m_renderableChunkMap;
	std::queue<std::pair<Vector3, ChunkMeshPtr>> m_meshToLoad;
	Shader m_chunkShader;
};