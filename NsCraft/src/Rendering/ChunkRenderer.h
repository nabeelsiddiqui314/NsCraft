#pragma once

struct Vector3;
class ChunkMesh;

class ChunkRenderer {
public:
	ChunkRenderer() = default;
	~ChunkRenderer() = default;
public:
	void addMesh(const Vector3& position, const ChunkMesh& mesh);
	void removeMesh(const Vector3& position);
	void renderChunks();
};