#include "CrossMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../Geometry/BlockFaces.h"
#include "../../World/Chunk/PaddedChunk.h"

CrossMeshGenerator::CrossMeshGenerator(GLuint texture) 
	: m_texture(texture) {}

void CrossMeshGenerator::generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) {
	std::uint8_t skyLight = chunk.getNode(position).skyLight;
	std::uint8_t naturalLight = chunk.getNode(position).naturalLight;

	mesh.addQuad(m_texture, BlockFaces::CrossA, skyLight, naturalLight);
	mesh.addQuad(m_texture, BlockFaces::CrossB, skyLight, naturalLight);
}