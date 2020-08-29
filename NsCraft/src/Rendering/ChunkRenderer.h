#pragma once
#include <unordered_map>
#include <memory>
#include "../Math/Vector3.h"

#include "../OpenGL/Texture.h"
#include "../OpenGL/Shader.h"

class ChunkMesh;
class Camera;
class VertexArray;

class ChunkRenderer {
private:
	typedef std::shared_ptr<VertexArray> VaoPtr;
public:
	ChunkRenderer();
	~ChunkRenderer() = default;
public:
	void addMesh(const Vector3& position, const ChunkMesh& mesh);
	void removeMesh(const Vector3& position);
	void renderChunks(const Camera& camera);
private:
	std::unordered_map<Vector3, VaoPtr> m_renderableChunkMap;
	Shader m_chunkShader;

	// temporary
	Texture m_texture;
};