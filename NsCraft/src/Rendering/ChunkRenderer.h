#pragma once
#include <memory>

struct Vector3;
class ChunkMesh;


class ChunkRenderer {
public:
	ChunkRenderer() = default;
	~ChunkRenderer() = default;
public:
	void addMesh(const Vector3& position, const std::shared_ptr<ChunkMesh>& mesh);
	void removeMesh(const Vector3& position);
	void renderChunks();
};