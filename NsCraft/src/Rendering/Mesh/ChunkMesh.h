#pragma once

class ChunkMesh {
public:
	ChunkMesh() = default;
	~ChunkMesh() = default;

	ChunkMesh(const ChunkMesh&) = delete;
	ChunkMesh& operator=(const ChunkMesh&) = delete;
};