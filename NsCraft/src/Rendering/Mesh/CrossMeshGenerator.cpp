#include "CrossMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../Geometry/BlockFaces.h"

CrossMeshGenerator::CrossMeshGenerator(GLuint texture) 
	: m_texture(texture) {}

void CrossMeshGenerator::generateMesh(ChunkMesh& mesh, const Neighborhood& neighborhood) {
	std::uint8_t skyLight = neighborhood.centre.getSkyLight();
	std::uint8_t naturalLight = neighborhood.centre.getNaturalLight();

	mesh.addQuad(m_texture, BlockFaces::CrossA, skyLight, naturalLight);
	mesh.addQuad(m_texture, BlockFaces::CrossB, skyLight, naturalLight);
}